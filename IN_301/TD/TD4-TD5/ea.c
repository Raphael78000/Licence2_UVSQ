#include <stdio.h>
#include <stdlib.h>
#include "ea.h"

/*
 * allocation de sizeof(struct Noeud) pour V;
 * affectation : op_ou_val = 0;
 * 				 val = val;
 * 				 op = NULL;
 * 				 Noeuds = NULL;
 * retourner la variable locale de type EA
 */
EA ea_creer_valeur (float val)
{
	EA V;
	V = malloc(sizeof(struct Noeud));
	V->op_ou_val = 1;
	V->op = '\0';
	V->val = val;
	V->sag = NULL;
	V->sad = NULL;
	printf("%f\n", V->val);
	return V;
}

/*
 * allocation sizeof(struct Noeud) pour O;
 * affectation : op_ou_val = 1;
 * 				 val = 0;
 * 		 		 op = op;
 * 				 Noeud droit = sad;
 * 			     Noeud gauche = sag;
 * retourner la variable locale de type EA
 */
EA ea_creer_operation (char op, EA sag, EA sad)
{
	EA O;
	O = malloc(sizeof(struct Noeud));
	O->op_ou_val = 0;
	O->val = 0;
	O->op = op;
	O->sag = sag;
	O->sad = sad;
	printf("%c\n", O->op);
	return O;
}

/*
 * ea_evaluer peut être utilisé récursivement. La condition de récursivité est si la fonction rencontre
 * un noeud contenant un opérateur (op_ou_val = 1). Cette récursivité nous permet de parcourir l'arbre
 * entièrement ( seulement les feuilles sont des floats ).
 */
float ea_evaluer (EA e)
{
	if ( e->op_ou_val == 0 ) 
	{
		printf("%c\n", e->op);
		switch (e->op)
		{
			case '+' : return ea_evaluer(e->sag)+ea_evaluer(e->sad);
					   break;
			case '-' : return ea_evaluer(e->sag)-ea_evaluer(e->sad);
					   break;
			case '*' : return ea_evaluer(e->sag)*ea_evaluer(e->sad);
					   break;
			case '/' : return ea_evaluer(e->sag)/ea_evaluer(e->sad);
					   break;
			case '(' : 
			case ')' : printf("parenthèses dans l'arbre\n");
						return -999.99;
					   break;
			default : printf("Erreur de symbole\n");
					  return -999.99;
					   break;
		}
	}
	else return e->val;
}

void ea_liberer ( EA f )
{
	free(f);
}

void afficher_arbre (EA e)
{
	if ( e->sag != NULL ) afficher_arbre(e->sag);
	if ( e->op_ou_val == 1 ) printf("%f\n", e->val);
	else printf("%c\n", e->op);
	if ( e->sad != NULL ) afficher_arbre(e->sad);
}
