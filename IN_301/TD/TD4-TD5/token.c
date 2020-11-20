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

	nouv=token_creer(val);//Etape 1+2
	//Etape 3:trouver le dernier element de la liste 
	if(t==NULL) return nouv;
	dernier=t;
	while( dernier->suiv !=NULL)dernier=dernier->suiv;
	//Etape 4:le suivant du dernier element est nouv
	dernier->suiv=nouv;
	nouv->prec=dernier;
	//Etape 5:Renvoyer la tete de liste 
	return t;
}

void token_afficher (TOKEN t){

	if (t==NULL) printf("\n");
	else{
		printf("%1.2f ",t->val);//Permet de mettre 1 chiffre avant virugle et 2 après virgule
		token_afficher(t->suiv);
	}
}