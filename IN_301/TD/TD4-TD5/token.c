#include "token.h"
#include <stdio.h>
#include <stdlib.h>

TOKEN token_creer(int type, char op, float val)
{
	TOKEN t;

	t = malloc(sizeof(struct token));
	if (t == NULL) exit(2);
	t->type_token = type;
	t->op = op;
	t->val = val;
	t->suiv = NULL;
	t->prec = NULL;
	return t;
}

TOKEN token_ajouter_fin_liste (TOKEN t, TOKEN nouv)
{
	TOKEN  dernier;


	// Etape 3 : trouver le dernier élément de la liste
	if (t == NULL) return nouv;

	dernier = t;
	while ( dernier->suiv != NULL) dernier = dernier->suiv;
	// Etape 4 : le suivant du dernier élément est nouv
	dernier->suiv = nouv;
	nouv->prec = dernier;
	// Etape 5: renvoyer la tête de liste
	return t;
}

//Version itérative

void token_afficher(TOKEN t)
{
	TOKEN tmp;

	tmp = t;

	while (tmp != NULL)
	{
		if (tmp->type_token == PAR_OUV) printf(" (");
		if (tmp->type_token == PAR_FER) printf(" )");
		if (tmp->type_token == OP) printf(" %c",tmp->op);
		if (tmp->type_token == VAL) printf(" %1.2f ",tmp->val);
		tmp = tmp->suiv;
	}
	printf("\n");
}

//Version récursive

void token_afficher_rec(TOKEN t)
{
	if (t == NULL) printf("\n");
	else
	{
		printf("%1.2f ",t->val);
		token_afficher_rec(t->suiv);
	}
}

int est_op(char c)
{
	if (c == '+') return 1;
	if (c == '*') return 1;
	if (c == '/') return 1;
	if (c == '-') return 1;
	return 0;
}

int est_val(char c)
{
	if (c >= '0' && c <='9') return 1;
	if (c == '.') return 1;
	return 0;
}

int est_valide(char c)
{
	if (c == '(') return 1;
	if (c == ')') return 1;
	if (est_op(c)) return 1;
	if (est_val(c)) return 1;
	if (c == ' ') return 1;
	return 0;
}

TOKEN token_creer_val(char **s)
{
	TOKEN e = token_creer(VAL,0,0.0);
	float mult = 0.1;

	// Avant le .(décimal)
	while (**s >= '0' && **s <= '9')
	{
		e->val = 10 * e->val + (**s -'0');
		(*s)++;
	}
	if (**s != '.') return e;
	// Après le . (décimal)
	(*s)++;
	while (**s >= '0' && **s <= '9')
	{
		e->val = e->val + mult*(**s - '0');
		mult = mult * 0.1;
		(*s)++;
	}
	(*s) --; // on a lu le prochain caractère à la fin
			// de la boucle précédente
			// et on va aussi dans la fonction creer_liste
			// lire le prochain caractère donc on risque de
			// sauter un caractère. Il faut donc revenir en arrière.
	return e;
}


TOKEN token_creer_liste(char *s)
{
	TOKEN t = NULL;
	TOKEN e;

	while( *s != '\0')
	{
		if (!est_valide(*s))
		{
			fprintf(stderr,"caractère non valide \n");
			exit(3);
		}
		if (*s == '(')
		{
			e = token_creer(PAR_OUV,0,0);
			t = token_ajouter_fin_liste(t,e);
		}
		if (*s == ')')
		{
			e = token_creer(PAR_FER,0,0);
			t = token_ajouter_fin_liste(t,e);
		}
		if (est_op(*s))
		{
			e = token_creer(OP,*s,0);
			t = token_ajouter_fin_liste(t,e);
		}
		if (est_val(*s))
		{
			e = token_creer_val(&s);
			t = token_ajouter_fin_liste(t,e);
		}

		s++;
	}

	return t;
}
