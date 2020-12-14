#include <stdlib.h>
#include <stdio.h>
#include "tableaux.h"
#include "chrono.h"

#define alphabet(x) (('a' <= (x) && (x) <= 'z')||( 'A' <= (x) && (x) <= 'Z' ))?1:0
// Ce que remplace la macro alphabet(x) renvoie VRAI si la variable est une lettre soit minuscule soit
// majuscule de l'alphabet latin dans la table ASCII, faux sinon

#define minuscule(x) ( 'A' <= (x) && (x) <= 'Z' )?( (x) + 0x20 ):(x)
// Ce que remplace la macro minuscule(x) renvoie la version minuscule de la lettre si elle est en majuscule,
// renvoie la lettre intacte sinon. Pour bien fonctionner, il faut que la variable renvoie VRAI quand elle
// est mise en argument de la macro alphabet(x)

#define scan(x) fscanf(f,"%c",&(x)) != EOF
// Ce que remplace la macro scan(x) est une condition qui est égale à FAUX quand on a atteint la fin du texte à scanner


// La fonction get_valeurs renvoie une variable de type TAB où sont stockées les sous-variables taille_char, nb_mots, nb_lignes et max_mot.
// En argument est le nom du fichier sous la forme d'une chaîne de caractères que l'on souhaite stocker dans les tableaux par la suite.
TAB get_valeurs( char* fichier )
{
	FILE* f = fopen(fichier, "r");			// Ouverture du ficher en mode lecure noté "r".
	if ( !f )								
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans get_valeurs!\n");
		exit(1);
	}
	
	char c;									// Le caractère c nous servira à stocker chaque caractère du texte. On n'utilisera pas ses valeurs par la suite 
	int taille_mot = 0;						
	TAB B;									// La variable de type TAB nommé B va être celle qui va être renvoyée. Dedans seront stockées les valeurs du nombre de caractère, nombre de mots, du nombres de lignes et la longueur du plus long mot du texte.
	
	B = malloc(sizeof(struct tableaux));			// On alloue la taille d'un struct tableaux pour la variable B de type struct tableaux*.
	B->taille_char = 0;								
	B->nb_mots = 0;									
	B->max_mot = 0;									
	B->nb_lignes = 2;								// On initialise le nombre de lignes à 2, une pour la 0ème ligne du texte à l'indice 0 et une pour la dernière ligne, qui ne se termine pas forcément par un retour chariot					
	B->T = NULL;									
	B->L = NULL;									// Pour l'instant, on initialise les deux tableaux en les faisant pointer nulle part.
	
	while( scan(c) )										// Tant qu'on a pas atteint la fin du texte faire
	{               										
		if ( alphabet(c) ) 									// On vérifie sur le caractère lu est une lettre
		{                      								
			taille_mot++;  									// On augmente de 1 taille_mot si c'est le cas
		}		
		else 												// Sinon 												
		{
			if ( taille_mot )								// Si un mot vient de se terminer alors
			{           
				B->nb_mots++;                 		      	// On augmente le nombre de mots de 1
				if ( taille_mot > B->max_mot )				// Si le mot est plus grand que tout les mots précédents alors on modifie la valeur du mot le plus long
				{          
					B->max_mot = taille_mot;				
				}
				taille_mot = 0;                  	        // On passe à un nouveau mot
			}
			if ( c == '\n' ) 								// Si le caractère scanné est un retour chariot alors on augmente le nombre de lignes de 1
			{
				B->nb_lignes++;								
			}	
		}
		B->taille_char++;									// On est sur le point de passer au caractère suivant donc on augmente de 1 le nombre de caractère du texte 
	}
	
	fclose(f);				// On ferme le fichier ouvert en début de fonction                           	                                  
	return B; 				// On retourne la variable B contenant les bonnes valeurs 
}						  


// La fonction init_tableaux réserve l'espace nécessaire pour utiliser une variable de type TAB selon le fichier dont le nom est passé en argument.
TAB init_tableaux ( char* fichier )
{
	TAB A;								// La variable de type TAB nommé A va être celle qui va être renvoyer. 
	
	A = get_valeurs(fichier);			// A contient les bonnes valeurs grâce à la fonction get_valeurs 
	
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
	
	return A;		// A la fin de la fonction, la variable A a les bonnes valeurs en plus d'avoir ses espaces de stockages réservées 
}				


// La fonction remplir_tableau renvoie une variable de type TAB dans laquelle est stockée tout les caractères et 
// tout les mots du texte ainsi que la premier caractère et le premier mot de chaque ligne non vide. 
TAB remplir_tableaux(char* fichier, double* temps)
{
	chrono_reset();
	double m;
	TAB C = init_tableaux(fichier);			// On initialise la variable locale C avec la fonction init_tableaux
	
	FILE* f = fopen(fichier, "r");		// Ouverture du ficher en mode lecure noté "r". 
	if ( !f )							
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans remplir_tableaux!\n");
		exit(1);
	}
	
	int n_char = 0;					
	int n_mot = 0;					
	int n_lettre = 0;				
	int n_ligne = 1;				
	int if_mot = 0;					// La variable if_mot prend la valeur 1 si un mot a été créé ou s'il est un cours de création dans le tableau T. Il prends la valeur 0 sinon.
	int RL = 1;						// La variable RL fonctionne de la même manière que if_mot : si la ligne a au moins au caractère, RL vaut 1. Elle vaut 0 sinon.
	
	
	C->L[0] = C->C[0] = -1;			// La ligne numéro 0 n'existe pas, on lui assigne la valeur -1 par défaut
	C->L[1] =  0;					// La 1er ligne commence toujours par la premier caractère du premier mot, c'est-à-dire le premier caractère du texte
	
	
	char* s; 													// La chaîne de caractère s va stocker le mot courant avant d'être stocké dans M[n_mot]
	s = malloc(sizeof(char)*C->max_mot);						// Le mot le plus long que s va rencontrer va faire la taille de max_mot, donc on alloue la mémoire en conséquent
	for ( int i = 0; i < C->max_mot; i++ ) s[i] = '\0';			// Sans porter de mot, s ne contient que des caractères de fin de chaîne de caractère


	while( scan(C->T[n_char]) )												// Tant qu'on peut stocker des caractères dans T
	{                 
		if ( alphabet(C->T[n_char]) ) 										// Si le caractère appartient à l'alphabet latin alors
		{                        
			s[n_lettre] = minuscule(C->T[n_char]);							// On stocke la lettre à la n_lettre position dans s et on passe à la prochaine
			n_lettre++;														
			if_mot = 1;														
			RL = 1;															 
		}
		else 																// Sinon
		{       
			if ( C->T[n_char] == '\n' )										// Si le caractère scanné est un retour chariot  
			{	
				if ( RL )													// Si la ligne n'est pas vide 
				{
					C->C[n_ligne] = n_mot;									// Le mot suivant du dernier mot de la ligne actuel est celui à l'indice n_mot dans C
					RL = 0;													// Maintenant que l'on va passer à une nouvelle ligne, on dit qu'elle est vide par défaut. 
					
				}
				else  C->C[n_ligne] = -1;									// Sinon C[n_ligne] prend la valeur de -1 pour signifier qu'il y a aucun mot sur cette ligne 
				C->L[n_ligne+1] = n_char+1;									// Le premier caractère de la prochaine ligne est le caractère suivant 
				n_ligne++;													// On avance d'une ligne 
			}
			if ( if_mot ) 													// Si un mot était en cours de création  
			{
				C->M[n_mot] = malloc(sizeof(char)*n_lettre+1);			    // On alloue la taille du mot + 1 caractère de fin de chaîne 
				for ( int k = 0; k <= n_lettre; k++ )						// On recopie s dans C->M[n_mot] et on réinitialise s
				{	
					C->M[n_mot][k] = s[k];									
					s[k] = '\0';											
				}	
				n_lettre = 0;												// On va commencer un nouveau mot 
				n_mot++;													// on avance d'un mot 
				if_mot = 0;													// Plus aucun mot n'est en cours de création.
			}
		}
		n_char++;															// On avance d'un caractère 
	}
	
	free(s);			// Nous avons plus besoin de la chaîne de caractère s donc on la libère
	fclose(f);			// On ferme le fichier ouvert en début de fonction           
	FILE* g = fopen ("Resultat.txt", "w");
	if ( !g )
	{
		printf("Il y a eu un problème avec l'ouverture du fichier Resultat.txt\n");
		exit(1);
	}
	m = chrono_lap()*1000;
	fprintf(g, "\n\n#########	 Le traitement du texte %s a mis %f millisecondes\n\n\n", fichier, m);
	*temps = *temps + m;
	fclose(g);                                        
	return C; 			// On renvoie la variable C avec toutes les bonnes valeurs stockées dans les tableaux T, L, M et C
}


// La fonction afficher_tableaux_TL affiche le texte en utilisant les tableaux T et L dans un fichier TL.txt
// En plus d'afficher tout le texte, on rajoute le numéro de ligne à chaque début de ligne
void afficher_tableaux_TL ( TAB D )
{
	FILE* f = fopen("TL.txt", "w");								// S'il existe déjà, on ouvre le fichier TL.txt en mode écriture noté "w". Sinon, on le crée puis on l'ouvre.
	if ( !f )							
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans remplir_tableaux!\n");
		exit(1);
	}
	
	int n_ligne = 1; 											

	for ( int i = 0; i < D->taille_char; i++ )					// De O à taille_char faire
	{
		if ( D->L[n_ligne] == i )								// Si le i-ème caractère dans T est un début de ligne 
		{
			fprintf(f,"(%5d)", n_ligne);						// Afficher le numéro de ligne entre parenthèse sur un espace de 4 caractères
			n_ligne++;											// Avancer d'une ligne 
		}
		fprintf(f, "%c", D->T[i]);								// Afficher le i-ème caractère dans T
	}

	fclose(f);													// On ferme le fichier TL.txt ouvert en début de fonction 
}


// La fonction afficher_tableaux_MC affiche le texte en utilisant les tableaux M et C dans un fichier MC.txt
// Le fichier contient tout les mots du texte en minuscule. Chaque mot affiché appartient au même numéro de ligne que le fichier d'origine
void afficher_tableaux_MC ( TAB E )
{
	FILE* f=fopen("MC.txt","w");								// S'il existe déjà, on ouvre le fichier MC.txt en mode écriture noté "w". Sinon, on le crée puis on l'ouvre.
	if ( !f )							
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans remplir_tableaux!\n");
		exit(1);
	}
	
	int n_ligne = 1;											
	
	for ( int i = 0; i < E->nb_mots; i++)						// De O à nb_mots faire
	{	
		while ( E->C[n_ligne] == i || E->C[n_ligne] == -1 ) 	// Tant que le i-ème mot est le suivant du dernier de la ligne ou si la ligne est vide 
		{
			fprintf(f,"\n");									// Afficher un retour chariot 
			n_ligne++;											// Avancer d'une ligne 
		}
		fprintf(f, "%s ", E->M[i]);								// Afficher le i-ème mot 
	}
	
	fclose(f); 													// On ferme le fichier MC.txt ouvert en début de fonction 
}
