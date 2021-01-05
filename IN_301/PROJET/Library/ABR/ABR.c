#include <stdio.h>
#include <stdlib.h>
#include "./../tableaux/tableaux.h"
#include "ABR.h"
#include "./../AVL/AVL.h"
#include "./../chrono/chrono.h"

// La fonction init_liste initialise un élément de type liste avec la valeur mise en argument, qui est le numéro de ligne 
LISTE init_liste ( int ligne )
{
	LISTE L;								
	L = malloc(sizeof(struct liste));		
	if ( !L ) 								// Si L est égale à NULL, alors il y a eu un problème dans l'allocation de mémoire et on sort du programme
	{										
		printf("Il y a eu un problème avec l'allocution en mémoire d'un des élément d'une liste\n");
		exit(1);
	}
	L->ligne = ligne;						// On lui affecte l'entier mis en argument
	L->suiv = NULL;							// L'élément suivant n'est pas encore connue, donc on affecte NULL au pointeur
	return L;								
}


// La fonction inserer_ligne insère dans la liste mise en argument l'entier mise en argument. Ici l'entier est un numéro de ligne
LISTE inserer_ligne ( LISTE L, int ligne )
{
	if ( !L ) return init_liste(ligne);					// Si la liste est vide, on y ajoute un élément 
	else if ( L->ligne == ligne ) return L;				// Sinon si la ligne qu'on cherche à insérer existe déjà, on arrête les appels récursifs et on retourne la liste intacte
	else 												
	{
		L->suiv = inserer_ligne(L->suiv, ligne);		
		return L;										
	}
}


// La fonction init_noeud initialise un élément de type noeud avec le mot ( suite de caractères ) et l'entier en arguments.
ARBRE init_noeud ( char* s, int ligne )
{
	ARBRE I;											
	I = malloc(sizeof(struct noeud));					
	if ( !I ) 											// Si I est égale à NULL, alors il y a eu un problème dans l'allocation de mémoire et on sort du programme
	{													
		printf("Il y a eu un problème avec l'allocution en mémoire d'un des noeuds\n");
		exit(1);
	}
	I->mot = s;											// La sous-variable mot de I est la chaîne de caractère mise en argument
	I->occ = 1;											// La sous-variable occ de I prend la valeur 1 car si le noeud existe alors I->mot apparait au moins une fois
	I->sag = NULL;										// Les sous-arbres droit et gauche de I ne sont pas encore définis alors on leur affecte alors la valeur de NULL
	I->sad = NULL;										
	I->num_ligne = NULL;								// La liste du noeud I n'est pas encore créée, on lui donne alors la valeur de NULL
	I->num_ligne = inserer_ligne(I->num_ligne, ligne);  // On lui ajoute le numéro de ligne qui est l'entier mis en argument
	return I;											
}


// La fonction compamots compare deux mots, mis en argument. On va appeler récursivement la fonction tant que les lettres sont identiques.
// On s'arrêtera lorqu'on rencontrera des lettres différentes ou quand on rencontrera un caractère signifiant la fin d'un mot 
int compamots ( char* mot1, char* mot2 ) 
{
	if ( (*mot1) != (*mot2) || *mot1 == '\0' || *mot2 == '\0' ) return ((*mot1)-(*mot2));	
	else return compamots((mot1)+1, (mot2)+1);												
}


// La fonction inserer_noeud insère un noeud qui a pour mot la variable en argument s et pour ligne la variable en argument ligne.
// Ce noeud sera inséré dans l'arbre A en argument si le mot n'existe pas encore dans ce dernier
ARBRE inserer_noeud ( ARBRE A, TAB T, int mot, int ligne )
{
	if ( !A ) return init_noeud ( T->M[mot], ligne );				// Si nous sommes dans un arbre nul, alors le mot n'existe pas et on peut l'insérer dans l'arbre 
	else 															
	{																// Autrement, on stocke dans une variable locale sup_inf la valeur donnée par la fonction compamots
		int sup_inf = compamots(A->mot, T->M[mot]);							
		if ( sup_inf < 0 )											// Si s est supérieur à A->mot
		{
			A->sad = inserer_noeud(A->sad, T, mot, ligne);			// On doit insérer le noeud dans son sous-arbre gauche
			A = desequilibre(A);									// On vérifié le déséquilibre du noeud après modification
			return A;												
		}
		else if ( sup_inf > 0 )										// Sinon si s est inférieur à A->mot
		{	
			A->sag = inserer_noeud(A->sag, T, mot, ligne);			// On doit insérer le noeud dans son sous-arbre droit
			A = desequilibre(A);									// On vérifié le déséquilibre du noeud après modification 
			return A;												
		}
		else 														// Sinon A->mot et s sont identiques alors
		{
			A->occ++;												
			A->num_ligne = inserer_ligne(A->num_ligne, ligne);		// On insère le numéro de ligne dans la liste de A
			free(T->M[mot]);										// On libère le mot qui apparaît plus d'une fois 
			T->M[mot] = NULL;										// On donne NULL à l'adresse du mot libéré
			return A;												
		}
	}
}


// Cette fonction affiche le contenu d'un noeud, c'est-à-dire son mot, son nombre d'occurence et ses numéros de ligne
void afficher_noeud ( ARBRE A )
{
	FILE* f = fopen("Contenu_Arbre.txt", "a");													// On ouvre le fichier Contenu_Arbre.txt en mode "a" pour ajouter du contenu
	if ( !f )							
	{
		printf("Il y a eu erreur lors de l'ouverture du fichier dans remplir_tableaux!\n");
		exit(1);
	}
														
	fprintf(f, "\n\n");																			
	if ( A->occ-1 ) fprintf(f, "'%s' apparaît %d fois sur les lignes  :   ", A->mot, A->occ);	// On affiche le mot et les lignes avec ligne au pluriel si A->occ > 2
	else fprintf(f, "'%s' apparaît sur la ligne  ", A->mot);									// Sinon on affiche la même chose avec ligne au singulier
	LISTE L = A->num_ligne;																		
	while ( L )																					// Tant que L n'est pas vide
	{
		fprintf(f, "%u   ", L->ligne);															// On affiche le nuémro de ligne contenu dans l'élément de la liste
		L = L->suiv;																			// On passe au prochain élément 
	}	
	fclose(f);																					// On ferme le fichier ouvert en début de fonction
}


// Cette fonction parcourt l'ensemble de l'arbre et appelle la fonction afficher_noeud de manière infixe
void afficher_arbre ( ARBRE A )
{
	if ( A->sag ) afficher_arbre(A->sag);		
	afficher_noeud(A);							
	if ( A->sad ) afficher_arbre(A->sad);		
}


// La fonction TAB_to_ARBRE insère dans un arbre tout les mots du tableau M contenu dans la structure tableaux sur laquelle pointe la variable en argument
ARBRE TAB_to_ARBRE (TAB T, double* temps)
{
	double n;
	chrono_reset();
	int ligne = 1;														
	ARBRE A = NULL;														
	for ( int i = 0; i < T->nb_mots; i++ )								
	{
		while ( T->C[ligne] == i || T->C[ligne] == -1 ) ligne++;		// Tant que le mot actuel est le prochain ou que la ligne est vide, on augmente le nombre de lignes
		A = inserer_noeud(A, T, i, ligne);
	}
	
	FILE* f = fopen ("Resultat.txt", "a");
	if ( !f )
	{
		printf("Il y a eu un problème avec l'ouverture du fichier Resultat.txt\n");
		exit(1);
	}
	n = chrono_lap()*1000;
	fprintf(f, "#########	 La construction de l'arbre AVL a pris %f millisecondes\n\n\n\n", n);
	fprintf(f, ">>>>>>>>>    Résultats des recherches :\n\n\n");
	*temps += n;
	fclose(f);
	
	return A;															// On retourne l'arbre qui stocke les mots du texte et qui est h-équilibré
}
