#include <stdio.h>
#include <stdlib.h>
#include "ea.h"
#include "token.h"

// Si ( au début et ) à la fin, les retier.
// Si une des deux mais pas les deux => ERREUR
// Si aucune des deux => on ne modifie pas la liste des tokens
TOKEN retirer_parenthese (TOKEN t) {
	if (t==NULL) return t;
	TOKEN tt = t;
	int prof = 0;
	while (tt->suiv != NULL) {
		if (tt->type_token == PAR_O) prof++;
		if (tt->type_token == PAR_F) prof--;
		tt = tt->suiv;
	}
	if (tt->type_token == PAR_F) prof--;
	// On retire les ()
	if (	(t->type_token == PAR_O)
		&&	(tt->type_token == PAR_F)
		&&	(prof==0)) {
printf("On retire\n");
		// On retire la ( du début
		TOKEN pour_le_free;
		pour_le_free = t;
		t = t->suiv;
		t->prec = NULL;
		free(pour_le_free);
		// On retire la ) de la fin
		pour_le_free = tt;
		tt = tt->prec;
		tt->suiv = NULL;
		free(pour_le_free);
	}
	return t;
}

// Cherche le premier opérateur en dehors de ()
TOKEN chercher_operateur (TOKEN t) {
	int prof = 0;
	while (t && ((t->type_token != OP) || prof>0)) t = t->suiv;
	if (t==NULL) {
		fprintf(stderr,"Pas d'opérateur hors parenthèse\n");
		exit(33);
	}
	return t;
}

TOKEN token_pour_sag (TOKEN t, TOKEN op) {
	op->prec->suiv = NULL;
	op->prec = NULL;
	return t;
}

TOKEN token_pour_sad (TOKEN t, TOKEN op) {
	t = op->suiv;
	t->prec = NULL;
	op->suiv = NULL;
	return t;
}

EA transforme_un_token_en_ea (TOKEN t) {
	EA e;
	e = malloc(sizeof(struct noeud));
	if (!e) exit(34);
	if (t->type_token == PAR_O || t->type_token == PAR_F) {
		fprintf(stderr,"Parenthèse sans partenaire\n");
		exit(35);
	}
	if (t->type_token == OP)  {
		e->op_ou_val = EST_OP;
		e->op = t->op;
	}
	if (t->type_token == VAL) {
		e->op_ou_val = EST_VAL;
		e->val = t->val;
	}
	e->opg = e->opd = NULL;
	free(t);
	return e;
}



EA token_to_EA (TOKEN t) {
	EA e;
	if (t==NULL) return NULL;
	if ((t->prec==NULL) && (t->suiv==NULL)) {
		if (t->type_token != VAL) {
			fprintf(stderr,"Token de type %d ne doit pas être une feuille\n",t->type_token);
			exit(36);
		}
		e = malloc(sizeof(struct noeud));
		if (e == NULL) exit(37);
		e->op_ou_val = EST_VAL;
		e->val = t->val;
		e->opg = e->opd = NULL;
		return e;
	}
	TOKEN tt;
	do {
		tt = t;
		t = retirer_parenthese(tt);
	} while (tt != t);
	TOKEN op = chercher_operateur(t);
	TOKEN G, D;
	G = token_pour_sag (t,op);
//	token_afficher(G);
	D = token_pour_sad (t,op);
//	token_afficher(D);
	e = transforme_un_token_en_ea (op);
	e->opg = token_to_EA(G);
	e->opd = token_to_EA(D);
	return e;
}
