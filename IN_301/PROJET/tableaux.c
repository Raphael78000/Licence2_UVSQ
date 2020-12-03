#include <stdlib.h>
#include <stdio.h>
#include "tableaux.h"


// La fonction alphabet renvoie VRAI si le caractère mis en argument est une lettre de l'alphabet latin, FAUX sinon.
// On rappelle aussi que dans la table ascii les lettres de l'alphabet latin se suivent par ordre alphabétique.
int alphabet ( char c )
{														
	if ( 'a' <= c && c <= 'z' ) return 1; 				// Est-ce que c est une lettre minuscule ? Si oui alors renvoyer VRAI (1).
	else if ( 'A' <= c && c <= 'Z' ) return 1;			// Est-ce que c est une lettre majuscule ? Si oui alors renvoyer VRAI (1).
	else return 0;										// Si aucune des conditions au-dessus, cela veut dire que c n'appartient pas à l'alphabet latin, on renvoie donc FAUX (0).
}														


// La fonction minuscule renvoie la version minuscule de la lettre stockée dans le caractère passé en argument.
// Pour que cette fonction marche correctement, il faut s'assurer que la fonction alphabet renvoie VRAI 
// quand on lui donne c en argument. On rappelle également que chaque lettre a une différence de 20 en base 16 
// ( noté 0x en C ) entre leur forme minuscule et majuscule dans la table ASCII telle que 'A' + 20 = 'a'.
char minuscule ( char c )
{
	if ( 'A' <= c && c <= 'Z' ) return ( c + 0x20 );		// Est-ce que c est une majuscule ? Si oui alors renvoyer sa forme minuscule 
	else return c;											// Sinon, renvoyer la caractère intacte
}


// La fonction get_valeurs renvoie une variable de type TAB où sont stockées les sous-variables taille_char, nb_mots, nb_lignes et max_mot.
// En argument est le nom du fichier sous la forme d'une chaîne de caractères que l'on souhaite stocker dans les tableaux par la suite.
TAB get_valeurs( char* fichier )
{
	FILE* f = fopen(fichier, "r");			// Ouverture du ficher en mode lecure noté "r"
	if ( !f )								// Si f ne pointe sur rien ( f = NULL ) alors on affiche un message d'erreur et on arrête le programme
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans get_valeurs!\n");
		exit(1);
	}
	
	char c;									// Le caractère c nous servira à stocker chaque caractère du texte.
	int taille_mot = 0;						// L'entier taille_mot contient la taille du mot parcouru. Si aucun mot n'est parcourue, il vaut 0.
	TAB B;									// La variable de type TAB nommé B va être celle qui va être renvoyée. Dedans seront stockées les valeurs du nombre de caractère, nombre de mots, du nombres de lignes et la longueur du plus long mot du texte.
	
	B = malloc(sizeof(struct tableaux));			// On alloue la taille d'un struct tableaux pour la variable B de type struct tableaux*.
	B->taille_char = 0;								// On initialise le nombre de caractère du texte à 0
	B->nb_mots = 0;									// On initialise le nombre de mots à 0.
	B->max_mot = 1;									// On initialise la longueur du mot le plus long à 1 pour prendre en compte le caractère '\0' à la fin de chaque chaîne de caractère.
	B->nb_lignes = 2;								// On initialise le nombre de lignes à 2, une pour la 0ème ligne du texte à l'indice 0 et une pour la dernière ligne, qui ne se termine pas forcément par un retour chariot					
	B->T = NULL;									// Pour l'instant, on initialise les deux tableaux en les faisant pointer nulle part.
	B->L = NULL;									
	
	while( fscanf(f,"%c",&c) !=EOF )						// Tant qu'on a pas atteint la fin du texte faire
	{               
		if ( alphabet(c) ) 									// Si c appartient à l'alphabet latin alors
		{                      
			taille_mot++;  									// Augmenter la taille du mot de 1
		}		
		else 												// Sinon 
		{
			if ( taille_mot )								// Si taille_mot est plus grand que 0, c'est-à-dire qu'un mot vient de se terminer alors
			{           
				B->nb_mots++;                 		      	// Augmenter le nombre de mots de 1
				if ( taille_mot > B->max_mot )				// Si le mot est plus grand que tout les mots précédents alors
				{          
					B->max_mot = taille_mot;				// Stocker la taille du mot dans la variable contenant la longueur du plus grand mot
				}
				taille_mot = 0;                  	        // On passe à un nouveau mot, donc on donne 0 à taille_mot
			}
			if ( c == '\n' ) 								// Si le caractère scanné est un retour chariot alors
			{
				B->nb_lignes++;								// Cela signifie la fin d'une ligne donc on ajoute 1 au nombre de lignes
			}	
		}
		B->taille_char++;									// On est sur le point de passer au caractère suivant donc on augmente de 1 le nombre de caractère du texte avant
	}
	
	fclose(f);				// On ferme le fichier ouvert en début de fonction                           	                                  
	return B; 				// On retourne la variable B contenant les bonnes valeurs du nombre de caractères, du nombre de mots, du nombre de ligne et de la longueur du mot le plus long
}						  


// La fonction init_tableaux réserve l'espace nécessaire pour utiliser une variable de type TAB selon le fichier dont le nom est passé en argument.
TAB init_tableaux ( char* fichier )
{
	TAB A;								// La variable de type TAB nommé A va être celle qui va être renvoyer. Dedans seront stockées les 
										// valeurs du nombre de mots, du nombres de lignes et la longueur du plus long mot du texte
	A = get_valeurs(fichier);			// grâce à la fonction get_valeurs.
	
	A->T = malloc (sizeof(char)*A->taille_char);	// On alloue la taille du texte en caractère 
	if ( !(A->T) )									// S'il y a eu un problème lors de l'allocation de mémoire, afficher un message d'erreur et quitter le programme
	{
		printf("Problème d'allocution de mémoire pour le tableau T\n");
		exit(1);
	}
	
	A->M = malloc(sizeof(char*)*A->nb_mots);   		// On alloue la taille d'une adresse vers un caractère pour chaque mot du texte
	if ( !(A->M) )									// S'il y a eu un problème lors de l'allocation de mémoire, afficher un message d'erreur et quitter le programme
	{
		printf("Problème d'allocution de mémoire pour le tableau M ( première dimension )\n");
		exit(1);
	}

	A->L = malloc(sizeof(int)*A->nb_lignes);		// On alloue la taille d'un entier pour chaque ligne du texte
	if ( !(A->L) )									// S'il y a eu un problème lors de l'allocation de mémoire, afficher un message d'erreur et quitter le programme
	{
		printf("Problème d'allocution de mémoire pour le tableau L\n");
		exit(1);
	}
	
	A->C = malloc(sizeof(int)*A->nb_lignes);		// On alloue la taille d'un entier pour chaque ligne du texte
	if ( !(A->C) )									// S'il y a eu un problème lors de l'allocation de mémoire, afficher un message d'erreur et quitter le programme
	{
		printf("Problème d'allocution de mémoire pour le tableau L\n");
		exit(1);
	}
	
	return A;		// A la fin de la fonction, la variable A a les bonnes valeurs pour les sous-variables taille_char, nb_mots, nb_lignes et max_mot en plus d'avoir ses espaces de stockages réservées en fonctions du texte dont le nom est en argument.
}				


// La fonction remplir_tableau renvoie une variable de type TAB dans laquelle est stockée tout les caractères et 
// tout les mots du texte ainsi que la premier caractère et mot de chaque ligne non vide. 
TAB remplir_tableaux(char* fichier)
{
	TAB C = init_tableaux(fichier);			// On initialise la variable locale C avec la fonction init_tableaux
	
	FILE* f = fopen(fichier, "r");		// Ouverture du ficher en mode lecure noté "r"
	if ( !f )							// Si f ne pointe sur rien ( f = NULL ) alors on affiche un message d'erreur et on arrête le programme
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans remplir_tableaux!\n");
		exit(1);
	}
	
	int n_char = 0;					// La variable n_char indique la position du (n_char+1)-ème caractère dans le texte
	int n_mot = 0;					// La variable n_mot indique la position du (n_mot+1)-ème mot dans le texte
	int n_lettre = 0;				// La variable n_lettre indique la position de la (n_lettre+1)-ème lettre dans un mot
	int n_ligne = 1;				// La variable n_ligne indique la position de la (n_ligne)-ème ligne dans le texte
	int if_mot = 0;					// La variable if_mot prend la valeur 1 si un mot a été créé ou s'il est un cours de création dans le tableau T. Il prends la valeur 0 sinon.
	int RL = 1;						// La variable RL fonctionne un peu de la même manière que if_mot : si la ligne a au moins au caractère, RL vaut 1. Elle vaut 0 sinon.
	
	
	C->L[0] = C->C[0] = -1;			// La ligne numéro 0 n'existe pas, on lui assigne la valeur -1 par défaut
	C->L[1] =  0;					// La 1er ligne commence toujours par la premier caractère du premier mot, c'est-à-dire le premier caractère du texte
	
	
	char* s; 													// La chaîne de caractère s va stocker le mot courant avant d'être stocké dans M[n_mot]
	s = malloc(sizeof(char)*C->max_mot);						// Le mot le plus long que s va rencontrer va faire la taille de max_mot, donc on alloue la mémoire en conséquent
	for ( int i = 0; i < C->max_mot; i++ ) s[i] = '\0';			// Sans porter de mot, s ne contient que des caractères de fin de chaîne de caractère


	while( fscanf(f,"%c",&C->T[n_char]) !=EOF )								// Tant qu'on peut stocker des caractères dans T
	{                 
		if ( alphabet(C->T[n_char]) ) 										// Si c appartient à l'alphabet latin alors
		{                        
			s[n_lettre] = minuscule(C->T[n_char]);							// On stocke la lettre à la n_lettre position dans s 
			n_lettre++;														// Une fois la n_lettre position occupée, on passe à la prochaine lettre de s en incrémentant n_lettre
			if_mot = 1;														// if_mot prend la valeur de 1, signifiant qu'un mot est en cours de création 
			RL = 1;															// RL prend la valeur de 1, signifiant que la ligne a au moins un caractère et donc qu'elle n'est pas vide
		}
		else 																// Sinon
		{       
			if ( C->T[n_char] == '\n' )										// Si le caractère scanner est un retour chariot ( on rappelle qu'on est dans la (n_ligne-1)-ème ligne dans le texte
			{	
				if ( RL )													// Si la ligne n'est pas vide 
				{
					C->C[n_ligne] = n_mot;									// Après avoir rencontré un retour chariot, le dernier mot de la ligne actuel est le mot actuel 
					RL = 0;													// Maintenant qu'on va passer à une nouvelle ligne, on dit qu'elle est vide par défaut. Elle sera égale à 1 quand alphabet(C->T[n_char]) sera vrai
					
				}
				else  C->C[n_ligne] = -1;									// Sinon la ligne est vide, C[n_ligne] prend la valeur de -1 pour signifier qu'il y a aucun mot sur cette ligne 
				C->L[n_ligne+1] = n_char+1;									// Pour tout les retours de lignes, le premier caractère de la prochaine ligne est le caractère suivant 
				n_ligne++;													// On avance d'une ligne dans le tableau L et C car on a scanné un retour chariot
			}
			if ( if_mot ) 													// Si un mot était en cours de création avant de rencontrer un caractère ne faisant pas parti de l'alphabe latin
			{
				C->M[n_mot] = malloc(sizeof(char)*n_lettre+1);			    // On alloue la taille du mot qu'on a créé donné par n_lettre + 1 caractère de fin de chaîne pour le (n-mot)-ème mot
				for ( int k = 0; k <= n_lettre; k++ )						// (n_lettre+1) fois, on...
				{	
					C->M[n_mot][k] = s[k];									// ...recopie la lettre stockée à la position k dans s dans la k-ème position du (n_mot)-ème mot
					s[k] = '\0';											// ...redonne la valeur '\0' à s[k]
				}	
				n_lettre = 0;												// On va commencer un nouveau mot donc on remet la valeur de n_lettre à 0,
				n_mot++;													// on avance d'un mot dans le tableau M et
				if_mot = 0;													// on donne la valeur 0 à if_mot pour dire que plus aucun n'est en cours de création.
			}
		}
		n_char++;															// On avance d'un caractère dans le tableau T
	}
	
	free(s);			// Nous avons plus besoin de la chaîne de caractère s donc on la libère
	fclose(f);			// On ferme le fichier ouvert en début de fonction                                                     
	return C; 			// On renvoie la variable C avec toutes les bonnes valeurs stockées dans les tableaux T, L, M et C
}


// La fonction afficher_tableaux_TL affiche le texte en utilisant les tableaux T et L dans un fichier TL.txt
// En plus d'afficher tout le texte, on rajoute le numéro de ligne à chaque début de ligne
void afficher_tableaux_TL ( TAB D )
{
	FILE* f = fopen("TL.txt", "w");								// S'il existe déjà, on ouvre le fichier TL.txt en mode écriture noté "w". Sinon, on le crée puis on l'ouvre.
	
	int n_ligne = 1; 											// La variable n_ligne indique à quelle ligne on est

	for ( int i = 0; i < D->taille_char; i++ )					// De O à taille_char faire
	{
		if ( D->L[n_ligne] == i )								// Si le i-ème caractère dans T est un début de ligne 
		{
			fprintf(f,"(%4d)", n_ligne);						// Afficher le numéro de ligne entre parenthèse sur un espace de 4 caractères
			n_ligne++;											// Avancer d'une ligne 
		}
		fprintf(f, "%c", D->T[i]);								// Afficher le i-ème caractère dans T
	}

	fclose(f);													// On ferme le fichier TL.txt ouvert en début de fonction 
}


// La fonction afficher_tableaux_TL affiche le texte en utilisant les tableaux M et C dans un fichier MC.txt
// Le fichier contient tout les mots du texte en minuscule. Chaque mot affiché appartient au même numéro de ligne que le fichier d'origine
void afficher_tableaux_MC ( TAB E )
{
	FILE* f=fopen("MC.txt","w");								// S'il existe déjà, on ouvre le fichier MC.txt en mode écriture noté "w". Sinon, on le crée puis on l'ouvre.
	
	int n_ligne = 1;											// La variable n_ligne indique à quelle ligne on est
	
	for ( int i = 0; i < E->nb_mots; i++)						// De O à nb_mots faire
	{	
		while ( E->C[n_ligne] == i || E->C[n_ligne] == -1 ) 	// Si i-ème mot est le dernier de la ligne ou si la ligne est vide 
		{
			fprintf(f,"\n");									// Afficher un retour chariot 
			n_ligne++;											// Avancer d'une ligne 
		}
		fprintf(f, "%s ", E->M[i]);								// Afficher le i-ème mot 
	}
	
	fclose(f); 													// On ferme le fichier MC.txt ouvert en début de fonction 
}


// Dans la suite du programme, on ne servira pas des tableaux T et L. C'est pour cela que cette fonction free_TB libère seulement ces deux tableaux
void free_TL ( TAB H )
{
	free(H->T);					// On libère le tableau T
	free(H->L);					// On libère le tableau L
}


// A la fin de notre programme, il nous faudra libérer la mémoire prise pour mener à bien ce dernier. C'est pour cela que free_tableaux libère tout 
// les tableaux aussi que la structure tableaux sur laquelle pointe la variable mise en argument.
void free_tableaux ( TAB F )
{
	free(F->T);					// On libère le tableau T
	free(F->L);					// On libère le tableau L
	free(F->C);					// On libère le tableau C
	for ( int i = 0; i < F->nb_mots; i++) 
	{
		free(F->M[i]);			// Pour i de 0 à (nb_mots-1), on libère les tableaux M[i]
	}
	free(F->M);					// On libère le tableau M
	free(F);					// On libère le reste de la structure, c'est-à-dire les valeurs entières qu'elle stocke ( taille_char, nb_mots, nb_lignes et max_mot )
}

