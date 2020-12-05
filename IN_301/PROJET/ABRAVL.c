#include <stdio.h>
#include <stdlib.h>
#include "tableaux.h"
#include "ABRAVL.h"

LISTE init_liste ( int ligne )
{
	LISTE L;
	L = malloc(sizeof(struct liste));
	L->ligne = ligne;
	L->suiv = NULL;
	return L;
}

LISTE inserer_ligne ( LISTE L, int ligne )
{
	if ( !L ) return L = init_liste(ligne);
	else return inserer_ligne(L->suiv, ligne);
}

ARBRE init_noeud ( char* s, int ligne )
{
	ARBRE I;
	I = malloc(sizeof(struct noeud));
	if ( !I )
	{
		printf("Il y a eu un problème avec l'allocution en mémoire d'un des noeuds\n");
		exit(1);
	}
	I->mot = s;
	I->occ = 1;
	I->parent = NULL;
	I->sag = NULL;
	I->sad = NULL;
	I->num_ligne = inserer_ligne(I->num_ligne, ligne);
	return I;
}

int compamots ( char* mot1, char* mot2 ) // Pour les warnings, regarder la correction du BLOC 5
{
	if ( *mot1 == '\0' || *mot2 == '\0' || (*mot1) != (*mot2) ) return (*mot2)-(*mot1);
	else return compamots(mot1+1, mot2+1);
}

ARBRE inserer_noeud ( ARBRE A, ARBRE N )
{
	if ( !A ) return N;
	else
	{
		int sup_inf = compamots(A->mot, N->mot);
		if ( sup_inf > 0 )
		{
			A->sag = inserer_noeud(A->sag, N);
			return A;
		}
		else if ( sup_inf < 0 )
		{
			A->sad = inserer_noeud(A->sad, N);
			return A;
		}
		else
		{
			A->occ++;
			A->num_ligne = inserer_ligne(A->num_ligne, N->num_ligne->ligne);
			free_arbre (N);
			return A;
		}
	}
}

void afficher_arbre ( ARBRE A )
{
	if ( A->sag != NULL ) afficher_arbre(A->sag);
	printf("%s\n", A->mot);
	if ( A->sad != NULL ) afficher_arbre(A->sad);
}

void afficher_liste (LISTE a)
{
	while (a->ligne != NULL){
		printf("%d\n",a->ligne);
		a->ligne=a->suiv;
	}
}

void free_liste ( LISTE L )
{
	if ( L->suiv ) free_liste( L->suiv );
	free( L );
}

void free_arbre ( ARBRE A )
{
	if ( A->sag ) free_arbre(A->sag);
	if ( A->sad ) free_arbre(A->sad);
	free( A->mot );
	free_liste( A->num_ligne );
	free( A );
}

/*
int max (int a, int b)
{
	if (a<=b){
		return b;
	}
	else{
		return a;
	}
*/
/*
int hauteur (ARBRE A)
{
	if (A){
		return 1 + max (hauteur (A->sag) , hauteur (A->sad));
	}
	else{
		return -1;
	}
}
*/
/*
int equilibre (ARBRE A)
{
	if ((hauteur(A->sag)-hauteur(A->sad))=-1){
		return 0;
	}
	if ((hauteur(A->sag)-hauteur(A->sad))=1){
		return 0;
	}
	if ((hauteur(A->sag)-hauteur(A->sad))=0){
		return 0;
	}
	if ((hauteur(A->sag)-hauteur(A->sad))=2){
		if (hauteur(A->sag->sag)>hauteur(A->sag->sad){
			rotation_droite(A);
			return 1;
		}
		else{
			rotation_gauche(A->sag);
			rotation_droite(A);
			return 1;
		}
	}
	else{
		if (hauteur(A->sag->sag)>hauteur(A->sad->sag)){
			rotation_gauche(A);
			return 1;
		}
		else{
			rotation_droite(A->sad);
			rotation_gauche(A);
			return 1;
		}
	}
}
*/
LISTE ligne_mot (TAB A, char *s)
{
	LISTE n;
	LISTE a;

	for (int i = 0; i < A->nb_mots; i++){
		if (s == A->M[i]){
			inserer_ligne( n, i);
		}
	}
	while (n->ligne != NULL){
		for (int i = 0; i<A->nb_lignes; i++){
			if(A->C[i]>n->ligne){
				inserer_ligne( a, i);
				break;
			}
		}
		n->ligne=n->suiv;
	}
	return a;
}
