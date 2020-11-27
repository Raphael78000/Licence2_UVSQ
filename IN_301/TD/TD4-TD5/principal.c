#include <stdio.h>
#include <stdlib.h>
#include "ea.h"
#include "token.h"

int main ()
{
	TOKEN T = NULL;
	T = token_creer_liste("(2+2)*(3+(2+2))");
	token_afficher(T);
	
	
	/*TOKEN t = NULL;
	t = token_ajouter_fin_liste(t, 2.3);
	t = token_ajouter_fin_liste(t, 8);
	t = token_ajouter_fin_liste(t, 5.12);
	token_afficher(t);*/
	
	
	/*TOKEN T, U, V, W, X, Y; 
	EA E, F, G, H, I, J;
	
	T = token_creer_liste("12.3+4.56");
	E = token_to_ea(T);
	
	U = token_creer_liste("(1+2)");
	F = token_to_ea(U);
	
	V = token_creer_liste("1+(2*3)");
	G = token_to_ea(V);
	
	W = token_creer_liste("1+2*3");
	H = token_to_ea(W);
	
	X = token_creer_liste("(1+2)*(5-(4-3))");
	I = token_to_ea(X);
	
	Y = token_creer_liste("(1+2)*(((3-4)*(5+(6+7)))+(8-9))");
	J = token_to_ea(Y); */
	
	return 0;
}

/* BLOC 4 
int main ()
{
	// 12.3 + 4.56 = 16.86
	EA a, a1, a2;
	a1 = ea_creer_valeur(12.3);
	a2 = ea_creer_valeur(4.56);
	a = ea_creer_operation('+', a1, a2);
	printf("\n%f\n", ea_evaluer(a));
	free(a);	free(a1);	free(a2);
	
	// (1+2) = 3
	EA b, b1, b2;
	b1 = ea_creer_valeur(1);
	b2 = ea_creer_valeur(2);
	b = ea_creer_operation('+', b1, b2);
	printf("\n%f\n", ea_evaluer(b));
	free(b);	free(b1);	free(b2);
	
	// 1+(2*3) = 1+2*3 = 7
	EA c, c1, c2;
	c1 = ea_creer_valeur(2);
	c2 = ea_creer_valeur(3);
	c = ea_creer_operation('*', c1, c2);
	c1 = ea_creer_valeur(1);
	c2 = ea_creer_operation('+', c1, c);
	printf("\n%f\n", ea_evaluer(c2));
	free(c);	free(c1);	free(c2);
	
	// (1+2)*(5-(4-3)) = 12
	EA d, d1, d2, d3;
	d1 = ea_creer_valeur(4);
	d2 = ea_creer_valeur(3);
	d = ea_creer_operation('-', d1, d2);
	d1 = ea_creer_valeur(5);
	d2 = ea_creer_operation('-', d1, d);
	d1 = ea_creer_valeur(1);
	d = ea_creer_valeur(2);
	d3 = ea_creer_operation('+', d1, d);
	d = ea_creer_operation('*', d3, d2);
	printf("\n%f\n", ea_evaluer(d));
	free(d);	free(d1);	free(d2);	free(d3);			
	
	// (1+2)*(((3-4)*(5+(6+7)))+(8-9)) = -57
	EA e, e1, e2, e3;
	e1 = ea_creer_valeur(6);
	e2 = ea_creer_valeur(7);
	e = ea_creer_operation('+', e1, e2);
	e1 = ea_creer_valeur(5);
	e2 = ea_creer_operation('+', e1, e);
	e = ea_creer_valeur(3);
	e1 = ea_creer_valeur(4);
	e3 = ea_creer_operation('-', e, e1);
	e1 = ea_creer_operation('*', e3, e2);
	e2 = ea_creer_valeur(8);
	e3 = ea_creer_valeur(9);
	e = ea_creer_operation('-', e2, e3);
	e2 = ea_creer_operation('+', e, e1);
	e = ea_creer_valeur(1);
	e1 = ea_creer_valeur(2);
	e3 = ea_creer_operation('+', e, e1);
	e = ea_creer_operation('*', e3, e2);
	printf("\n%f\n", ea_evaluer(e));
	free(e);	free(e1);	free(e2);	free(e3);
	
	return 0;
}
*/
