#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "ea.h"

TOKEN token_creer(float val){
	TOKEN t;

	t=malloc(sizeof(struct token));
	t->val=val;
	t->suiv=NULL;

	return t;
}

TOKEN token_ajouter_fin_liste (TOKEN t,float val){
	TOKEN nouv,dernier;

	nouv=token_creer(val);//Creer un token avec la valeur et un pointeur qui pointe vers NULL
	if(t==NULL){//si la liste chaînée ne contient aucun element à cet instant
		return nouv;
	}
	dernier=t;//Creer un TOKEN qui pointe vers l'adresse du TOKEN principal
	while( dernier->suiv !=NULL){//Le pointeur pointe à partir du début de la liste chaînée
		dernier=dernier->suiv;//Permet d'accéder à la dernière valeure de la liste chaînée
		}
	dernier->suiv=nouv;//Sotck la valeur déclarée dans l'avant dernier element liste chaînée
	nouv->prec=dernier;//Permet de stocker la valeure précédente en même temps
	return t;//Renvoie la liste chaînée modifiée 
}

void token_afficher (TOKEN t){

	if (t==NULL) printf("\n");
	else{
		printf("%1.2f ",t->val);//Permet de mettre 1 chiffre avant virugle et 2 après virgule
		token_afficher(t->suiv);//Appel récursif au prochain element de la liste chaînée
	}
}