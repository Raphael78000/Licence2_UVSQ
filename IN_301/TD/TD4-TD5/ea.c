#include <stdio.h>
#include <stdlib.h>
#include "ea.h"

EA ea_creer_valeur (float val) {
	EA e;
	e = malloc(sizeof(struct noeud));
	if (e==NULL) exit(11);
	e->op_ou_val = EST_VAL;
	e->op  = NO_OP;
	e->val = val;
	e->opg = NULL;
	e->opd = NULL;
	return e;
}

int op_correct(char op) {
	if (op=='+') return 1;
	if (op=='-') return 1;
	if (op=='*') return 1;
	if (op=='/') return 1;
	return 0;
}


EA ea_creer_operation (char op, EA opg, EA opd) {
	if (op_correct(op) == 0) {
		fprintf(stderr,"Operateur '%c' non reconnu\n",op);
		exit(12);
	}
	EA e;
	e = malloc(sizeof(struct noeud));
	if (e==NULL) exit(13);
	e->op_ou_val = EST_OP;
	e->op  = op;
	e->val = NO_VAL;
	e->opg = opg;
	e->opd = opd;
	return e;
}

float ea_evaluer(EA e) {
	if (e==NULL) return 0.0;
	if (e->op_ou_val == EST_VAL) return e->val;

	float valg = ea_evaluer(e->opg);
	float vald = ea_evaluer(e->opd);
	if (e->op == '+') return valg + vald;
	if (e->op == '-') return valg - vald;
	if (e->op == '*') return valg * vald;

	if ((e->op == '/') && (vald  == 0.0)) {
		fprintf(stderr,"PB division par zéro\n");
		exit(14);
	}
	if (e->op == '/') return valg / vald;

	fprintf(stderr,"Normalement on n'arrive pas ici\n");
	exit(15);
	return 0;
}

void ea_afficher(EA e){
	if (e==NULL) return;
	if (e->op_ou_val == EST_VAL) printf("%.2f",e->val);
	else {
		printf("(");
		ea_afficher(e->opg);
		printf(" %c ",e->op);
		ea_afficher(e->opd);
		printf(")");
		}
}

