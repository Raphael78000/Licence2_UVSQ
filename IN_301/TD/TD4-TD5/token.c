#include <stdio.h>
#include <stdlib.h>

#include "token.h"

// Création d'un token
TOKEN creer_token (int type_token, char op, int val) {
	TOKEN e;
	e = malloc(sizeof(struct token));
	if (e==NULL) exit(21);
	e->type_token = type_token;
	e->op         = op;
	e->val        = val;
	e->suiv       = NULL;
	e->prec       = NULL;
	return e;
}

// Ajout d'un token à la fin de t
TOKEN token_ajouter_fin_liste (TOKEN t, TOKEN e) {
	// Cas de la liste vide
	if (t==NULL) return e;
	// Cas général
	TOKEN tdeb = t;
	// Déplacer t pour qu'il pointe 
	// sur le dernier élément de la liste
	while (t->suiv != NULL) {
		t = t->suiv;
	}
	t->suiv = e;
	e->prec = t;
	return tdeb;
}

// Renvoie VRAI si c est un opérateur reconnu
int est_op (char c) {
	if (c=='+') return 1;
	if (c=='*') return 1;
	if (c=='-') return 1;
	if (c=='/') return 1;
	return 0;
}

int est_chiffre (char c) {
	return (('0'<=c) && (c<='9'));
}
// Renvoie VRAI si le caractère peut être un caractère d'un float
// Dans la table ASCII, les codes pour les caractères 
// représentant les chiffres se suivent
int est_val (char c) {
	if (est_chiffre(c)) return 1;
	if (c=='.') return 1;
	return 0;
}

// Renvoie VRAI si le caractère peut apparître
// dans une expression arithmétique
int est_valide (char c) {
	if (c == '(')   return 1;
	if (c == ')')   return 1;
	if (est_op(c))  return 1;
	if (est_val(c)) return 1;
	if (c==' ')     return 1;
//	if (c=='\t')    return 1;
//	if (c=='\n')    return 1;
	return 0;
}


TOKEN creer_token_val (char **ps) {
	// création du token avec val qui vaut 0.0
	TOKEN e = creer_token (VAL,0,0.0);
	// On met dans val la partie entière
	while  (est_chiffre(**ps)) {
		e->val = 10*e->val  +  **ps-'0';
		(*ps)++;
	}

	if (**ps != '.') return e;
	(*ps)++;
	// On ajoute dans val la partie décimale
	float puissdix = 0.1;
	while  (est_chiffre(**ps)) {
		e->val += puissdix * (**ps-'0');
		puissdix = puissdix*0.1;
		(*ps)++;
	}
	return e;
}


TOKEN token_creer_liste (char *s) {
	TOKEN e;
	TOKEN t = NULL;
	int faut_avancer = 1;
	while (*s != '\0') {
		faut_avancer = 1;
		if (!est_valide(*s)) {
			fprintf(stderr," Caractere '%c' non valide\n",*s);
			exit(22);
		}
		if (*s == '(')  {
			e = creer_token (PAR_O,0,0);
			t = token_ajouter_fin_liste(t,e);
		}
		if (*s == ')')  {
			e = creer_token (PAR_F,0,0);
			t = token_ajouter_fin_liste(t,e);
		}
		if (est_op(*s)) {
			e = creer_token (OP,*s,0);
			t = token_ajouter_fin_liste(t,e);
		}
		if (est_val(*s)) {
			e = creer_token_val (&s);
			t = token_ajouter_fin_liste(t,e);
			// C'est la fonction creer_token_val qui a fait avancer s
			faut_avancer = 0;
		}
		if (faut_avancer) s++;
	}
	return t;
}




void token_afficher (TOKEN t) {
	printf("## DEB ##\n");
	while (t != NULL) {
		if (t->type_token == PAR_O) printf("PAR_O\n");
		if (t->type_token == PAR_F) printf("PAR_F\n");
		if (t->type_token == OP)    printf("OP    '%c'\n",t->op);
		if (t->type_token == VAL)   printf("VAL   %f\n",t->val);
		t = t->suiv;
	}
	printf("## FIN ##\n");
}
