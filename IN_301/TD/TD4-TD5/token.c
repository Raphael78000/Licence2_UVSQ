#include <stdio.h>
#include <stdlib.h> 
#include "ea.h"
#include "token.h"

/*
 * 1) On vérifie d'abord si le caractère n'est pas un '(' ou un ')'
 * 2) Dans ce cas-là, on dit que le token est de type 1 pour '(' ou
 *    de type 0 pour ')'
 * 3) On vérifie après si le caractère est un opétateur (+, -, *, /, %)
 * 4) Dans ce cas-là, on dit que le token est de type 2 et que la valeur 
 *    op du token est égal au caractère analysé.
 * 5) Finalement, si le caractère est un entier cad 31 <= 'c' <= 39 alors
 * 	  le token est de type 3 et prend comme valeur dans val ATOF ('c')
 * 6) Cas particulier : si le caractère est un espace,  l'ignorer ( 1er 
 * 	  condition ). Si le caractère est autre chose que tout ce qu'on a 
 * 	  demandé, sortir de la fonction avec un message d'erreur ( dernère 
 * 	  condition ).
 * 7) ne pas oublier de faire T2.prec = T1 et T1.suiv = T2
 */
 
TOKEN token_creer_val ( float val )
{
	TOKEN T;
	T = malloc(sizeof(struct token));
	T->type_token = 1;
	T->val = val;
	T->suiv = NULL;
	T->prec = NULL;
	return T;
}

TOKEN token_creer_op ( char op )
{
	TOKEN T;
	T = malloc(sizeof(struct token));
	T->type_token = 0;
	T->op = op;
	T->suiv = NULL;
	T->prec = NULL;
	return T;
}
 
TOKEN token_ajouter_fin_liste ( TOKEN t, TOKEN T )
{
	TOKEN U;
	if ( t == NULL ) return T;
	U = t;
	while ( U->suiv != NULL )
	{
		U = U->suiv;
	}
	U->suiv = T;
	T->prec = U;
	return t;
}

TOKEN token_creer_liste ( char* s )
{
	TOKEN t, T;
	int i;
	float e, d, dec;
	t = NULL;
	for ( i = 0; s[i] != '\0'; i++ ) 
	{
		e = 0; d = 0; dec = 0.1;
		if ( '0' <= s[i] && s[i] <= '9' )
		{
			while ( '0' <= s[i] && s[i] <= '9' )
			{
				dec = dec*10;
				e = e*dec + (s[i]-'0');
				i++;
				if ( s[i] == 46 ) 
				{
					dec = 0.1;
					i++;
					while ( '0' <= s[i] && s[i] <= '9' )
					{
						d =  d + (s[i]-'0')*dec;
						dec *= 0.1;
						i++;
					}
				}
			}
			i--;
			T = token_creer_val(e+d);
			t = token_ajouter_fin_liste ( t, T );
		}
		else if ( s[i] == 0x20 ) {}
		else 
		{
			T = token_creer_op(s[i]);
			t = token_ajouter_fin_liste ( t, T );
		}
	}
	return t;
}

EA token_to_ea ( TOKEN t )
{
	EA A = NULL;
	/*EA A, D = NULL, G = NULL;
	TOKEN T = t;
	if ( T->op == '(' ) 
	{
		G = token_to_ea(T->suiv);
		while ( T->op != ')' ) T = T->suiv;
		T = T->suiv;
	}
	else if ( T->type_token == 1 ) G = ea_creer_valeur(T->val);
	T = T->suiv->suiv;
	if ( T->op == '(' ) 
	{
		D = token_to_ea(T->suiv);
		while ( T->op != ')' ) T = T->suiv;
		T = T->suiv;
	}
	else if ( T->type_token == 1 ) D = ea_creer_valeur(T->val);
	T = T->prec;
	A = ea_creer_operation(T->op, G, D);*/
	return A;
}

void token_afficher( TOKEN t )
{
	if ( t == NULL ) printf("liste vide\n");
	TOKEN A = t;
	printf("\n");
	while ( A != NULL )
	{
		if ( A->type_token == 0 ) printf("%c ", A->op);
		else printf("%1.2f ", A->val);
		A = A->suiv;
	}
	printf("\n");  printf("\n");
	
	/*printf("%1.2f\n", A->val);
	printf("MIROIR\n");
	while ( A != NULL )
	{
		printf("%1.2f\n", A->val);
		A = A->prec;
	}*/
}
