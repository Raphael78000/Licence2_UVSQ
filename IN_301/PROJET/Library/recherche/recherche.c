#include <stdio.h>
#include <stdlib.h>
#include "./../tableaux/tableaux.h"
#include "./../ABR/ABR.h"
#include "./../AVL/AVL.h"
#include "recherche.h"
#include "./../chrono/chrono.h"

// La fonction afficher_recherche affiche le résultat d'une recherche 
void afficher_recherche ( ARBRE A, char* mot, TAB T )
{
	FILE* f = fopen("Resultat.txt", "a");														// On ouvre le fichier Contenu_Noeud.txt en mode "a" pour ajouter du contenu
	if ( !f )							
	{
		printf("Il y a eu erreur lors de l'ouverture due Contenu_Noeud.txt\n");
		exit(1);
	}
	
	fprintf(f, "-------->    ");
	if ( !A ) fprintf(f, "Le mot %s n'a pas été trouvé dans le texte\n\n", mot );						// Si A est NULL, alors le mot recherché n'a pas été trouvé
	else 
	{																															
		if ( A->occ-1 ) fprintf(f, "'%s' apparaît %d fois sur les lignes  :   ", A->mot, A->occ);	// Ce que contient else ressemble fortement à la fonction afficher_noeud()
		else fprintf(f, "'%s' apparaît sur la ligne  ", A->mot);	
		fprintf(f, "\n");									
		LISTE L = A->num_ligne;																		
		while ( L )																					
		{
			fprintf(f,"\n( %5d )    ", L->ligne);
			for ( int i = T->L[L->ligne]; i != T->L[L->ligne+1]; i++ ) fprintf(f, "%c", T->T[i]);	
			L = L->suiv;																		
		}	
		fprintf(f, "\n\n\n");
	}
	fclose(f);																						// On ferme le fichier ouvert en début de fonction
}


// La fonction recherche() recherche le mot s dans l'arbre A. Elle ressemble fortement à la fonction inserer_noeud		
ARBRE recherche ( ARBRE A, char* s )
{
	if ( !A ) return NULL;						
	else 															
	{													
		int sup_inf = compamots(A->mot, s);							
		if ( sup_inf < 0 ) return recherche ( A->sad, s);
		else if ( sup_inf > 0 ) return recherche ( A->sag, s);
		else return A;
	}

}


// La fonction mode_recherche determine quelles mots vont être recherchés.
void mode_recherche ( ARBRE A, TAB T, int argc, char** argv, double* temps)
{
	double o;
	
	// S'il y a des mots à rechercher dans la ligne de commandes, on ne recherche qu'eux
	if ( argc-2 ) 
	{
		for ( int k = 2; k < argc; k++ ) 
		{
			chrono_reset();
			afficher_recherche ( recherche ( A, argv[k] ), argv[k], T);
			FILE* f = fopen ("Resultat.txt", "a");
			if ( !f )
			{
				printf("Il y a eu un problème avec l'ouverture du fichier Resultat.txt\n");
				exit(1);
			}
			o = chrono_lap()*1000;
			fprintf(f, "( Temps )    La recherche du mot '%s' a pris %f millisecondes\n\n\n\n\n", argv[k], o);
			*temps += o;
			fclose(f);
		}
	}
	else 
	{
		chrono_reset();
		int r;								// Sinon on recherche 1000 mots aléatoires dans le texte
		srandom(getpid());
		for ( int j = 0; j < 1000; j++ )
		{
			r = (random()%(T->nb_mots));
			if ( T->M[r] ) afficher_recherche ( recherche ( A, T->M[r]), T->M[r], T);
			else j--;
		}	
		FILE* f = fopen ("Resultat.txt", "a");
		if ( !f )
		{
			printf("Il y a eu un problème avec l'ouverture du fichier Resultat.txt\n");
			exit(1);
		}
		o = chrono_lap()*1000;
		fprintf(f, "\n-------->    La recherche de 1000 mots aléatoires s'est terminé après %f millisecondes\n\n\n\n", o);
		*temps += o;
		fclose(f);
	}
}


// Cette fonction libère la mémoire prise par la liste mise en argument
void free_liste ( LISTE L )
{
	if ( L->suiv ) free_liste( L->suiv );	// Tant que l'élément suivant de la liste n'est pas vide, on appelle récursivement la fonction 
	free( L );								
}	


// Cette fonction libère un noeud ainsi que ses sous-arbres droit et gauche. Pour se faire, on fait un parcours postfixe.
// On notera qu'on ne peut pas libérer le mot du noeud car il a la même adresse que le mot dans le tableau M. 
void free_arbre ( ARBRE A )
{
	if ( A->sag ) free_arbre(A->sag);	
	if ( A->sad ) free_arbre(A->sad);							
	free_liste( A->num_ligne );			// On libère la liste en appelant la fonction free_liste
	free( A );							
}								


// A la fin de notre programme, il nous faudra libérer la mémoire prise pour mener à bien ce dernier.
// La fonction free_all libère les structures de données TAB T et ARBRE A réservée plus tôt dans le programme
void free_all ( TAB T, ARBRE A, double* temps)
{
	chrono_reset();
	free_arbre(A);
	free(T->T);					
	free(T->L);					
	free(T->C);					
	for ( int i = 0; i < T->nb_mots; i++) 
	{
		if ( T->M[i] ) free(T->M[i]);			// Pour i de 0 à (nb_mots-1), on libère les tableaux M[i] si ce n'est pas fait
	}
	free(T->M);					
	free(T);
	*temps = *temps + (chrono_lap()*1000);					
}
