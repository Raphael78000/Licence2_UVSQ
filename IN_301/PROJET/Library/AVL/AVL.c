#include <stdio.h>
#include <stdlib.h>
#include "./../tableaux/tableaux.h"
#include "./../ABR/ABR.h"
#include "AVL.h"


// La fonction hauteur renvoie la hauteur d'un arbre mis en arguement
int hauteur (ARBRE A)
{
	if (A) 
	{
		char a = hauteur (A->sag);
		char b = hauteur (A->sad);
		return 1 + max(a, b);	
	}	
	else return -1;													
}


// La fonction rotation_droite permet de faire une rotation à droite sur l'arbre mise en argument
ARBRE rotation_droite ( ARBRE A ) 
{
	ARBRE R, S; 		
	R = A->sag;			
	S = R->sad;			
	R->sad = A;			
	A->sag = S;			
	return R;			// R devient la nouvelle racine
}


// La fonction rotation_gauche permet de faire une rotation à gauche sur l'arbre mise en argument
ARBRE rotation_gauche ( ARBRE A ) 
{
	ARBRE R, S;			
	R = A->sad;			
	S = R->sag;			
	R->sag = A;			
	A->sad = S;			
	return R;			// R devient la nouvelle racine
}


//La fonction desequilibre calcule le déséquilibre de l'arbre mis en argument et fait des rotations en appelant les fonctions au-dessus si nécessaire	
ARBRE desequilibre ( ARBRE A )
{
	switch ( hauteur(A->sag)-hauteur(A->sad) ) // Si le déséquilibre de l'arbre en argument est égal à...
	{
		case -1 : 
		case  0 :  
		case  1 : return A; 
		
		// ... 2 alors il faut faire une rotatation à droite sur l'arbre en argument
		case 2 : switch ( hauteur(A->sag->sag)-hauteur(A->sag->sad) ) // Si le déséquilibre de son sous-arbre gauche est égal à...
				  {
					  case -1 : A->sag = rotation_gauche(A->sag);	  // ... -1 alors il faut faire une rotation en plus qui est une rotation à gauche sur son sous-arbre gauche
					  case  0 :											
					  case  1 : return rotation_droite (A);			  
					  
					  // Si passe par là, on a enfreint les règles d'un arbre AVL		
					  default : printf("L'arbre ne peut être équilibré à cause d'un déséquilibre non-traité\n");
								exit(1);
				  }
		
		// ... -2 alors il faut faire une rotatation à gauche sur l'arbre en argument  
		case -2 : switch ( hauteur(A->sad->sag)-hauteur(A->sad->sad) ) // Si le déséquilibre de son sous-arbre gauche est égal à...
				  {
					  case   1 : A->sad = rotation_droite(A->sad);	   // ... 1 alors il faut faire une rotation en plus qui est une rotation à droite sur son sous-arbre droit
					  case   0 :
					  case  -1 : return rotation_gauche (A);		   
					  
					  // Si passe par là, on a enfreint les règles d'un arbre AVL	
					  default : printf("L'arbre ne peut être équilibré à cause d'un déséquilibre non-traité\n");
								exit(1);
				  } 
				  
		// Si passe par là, on a enfreint les règles d'un arbre AVL		  
		default : printf("On a rencontré un déséquilibre plus petit que -2 ou plus grand que +2\n");
				  exit(1);
	}
}


// La fonction AVL renvoie vrai si l'arbre mis en argument est un arbre AVL, faux sinon
int AVL ( ARBRE A )
{
	if ( !A ) return 1;														// Si l'arbre est vide alors il est un arbre AVL
	else 																	
	{
		int dif = hauteur(A->sag)-hauteur(A->sad);							 
		if ( -1 <= dif && dif <= 1 ) return (AVL(A->sag) && AVL(A->sad));	
		else return 0;														// Sinon il y a un déséquilibre plus grand que 1 ou plus petit que -1, ce n'est pas un AVL
	}
}
