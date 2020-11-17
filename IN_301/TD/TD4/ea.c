#include <stdio.h>
#include <stdlib.h>
#include "ea.h"

EA ea_creer_valeur(float val){
	 EA e;
	 
	 e=malloc(sizeof(struct noeud));
	 (*e).op_ou_val=1;
	 (*e).val=val;
	 (*e).opg=NULL;
	 (*e).opd=NULL;
	 
	 return e;
}
 
EA ea_creer_operation(char op,EA opg,EA opd){
	 EA e;
	 
	 e=malloc(sizeof(struct noeud));
	 (*e).op_ou_val=0;
	 (*e).op=op;
	 (*e).opg=opg;
	 (*e).opd=opd;
	 
	 return e;
}
 
float ea_evaluer(EA e){
	if ((*e).op_ou_val==1) return (*e).val;//cas ou le noeud sur lequel on travaille est une valeur
	if ((*e).op=='+') return ea_evaluer((*e).opg)+ea_evaluer((*e).opd);//cas ou le noeud sur lequel on travaille est un opérateur
	if ((*e).op=='-') return ea_evaluer((*e).opg)-ea_evaluer((*e).opd);
	if ((*e).op=='/') return ea_evaluer((*e).opg)/ea_evaluer((*e).opd);
	if ((*e).op=='*') return ea_evaluer((*e).opg)*ea_evaluer((*e).opd);
	printf("erreur de symbole\n");
	
	return 0.000;
}
