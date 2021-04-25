
#ifndef __EA_H
#define __EA_H 1

#define EST_VAL 1
#define EST_OP  2
#define NO_VAL  3
#define NO_OP   4

struct noeud {
	int op_ou_val; 	// Vaut EST_VAL si le noeud est une feuille
					// Vaut EST_OP  si le noeud est un opérateur
	char op;
	float val;
	struct noeud *opg;
	struct noeud *opd;
};

typedef struct noeud * EA;

// Signatures des fonctions
EA ea_creer_valeur (float val);
EA ea_creer_operation (char op, EA opg, EA opd);
float ea_evaluer(EA e);
void ea_afficher(EA e);

#endif
