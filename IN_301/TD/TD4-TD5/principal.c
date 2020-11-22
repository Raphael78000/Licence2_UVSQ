#include <stdio.h>
#include <stdlib.h>
#include "ea.h"
#include "token.h"

int main(){

//TD4
/*
	EA e,e1,e2;
	EA f,f1,f2;
	EA g,g1,g2,g3,g4;
	EA h,h1,h2,h3,h4,h5,h6,h7,h8;
	EA k,k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14,k15,k16;
	
e1 = ea_creer_valeur(12.3);
e2 = ea_creer_valeur(4.56);
e = ea_creer_operation('+',e1,e2);
printf("%f\n",ea_evaluer(e));

f1=ea_creer_valeur(1);
f2=ea_creer_valeur(2);
f=ea_creer_operation('-',f1,f2);
printf("%f\n",ea_evaluer(f));

g3=ea_creer_valeur(2);
g4=ea_creer_valeur(3);
g2=ea_creer_operation('*',g3,g4);
g1=ea_creer_valeur(1);
g=ea_creer_operation('+',g2,g1);
printf("%f\n",ea_evaluer(g));

h8=ea_creer_valeur(4);
h7=ea_creer_valeur(3);
h6=ea_creer_operation('-',h8,h7);
h5=ea_creer_valeur(5);
h4=ea_creer_operation('-',h5,h6);
h3=ea_creer_valeur(1);
h2=ea_creer_valeur(2);
h1=ea_creer_operation('+',h2,h3);
h=ea_creer_operation('*',h1,h4);
printf("%f\n",ea_evaluer(h));

k16=ea_creer_valeur(6);
k15=ea_creer_valeur(7);
k14=ea_creer_operation('+',k16,k15);
k13=ea_creer_valeur(5);
k12=ea_creer_operation('+',k13,k14);
k11=ea_creer_valeur(3);
k10=ea_creer_valeur(4);
k9=ea_creer_operation('-',k11,k10);
k8=ea_creer_operation('*',k9,k12);
k7=ea_creer_valeur(1);
k6=ea_creer_valeur(2);
k5=ea_creer_operation('+',k7,k6);
k4=ea_creer_valeur(8);
k3=ea_creer_valeur(9);
k2=ea_creer_operation('-',k4,k3);
k1=ea_creer_operation('*',k2,k8);
k=ea_creer_operation('*',k5,k1);
printf("%f\n",ea_evaluer(k));
*/

//TD5

TOKEN t = NULL;
t = token_ajouter_fin_liste (t, 2.3);
t = token_ajouter_fin_liste (t, 8);
t = token_ajouter_fin_liste (t, 5.12);
t = token_ajouter_fin_liste (t, 10);
t = token_ajouter_fin_liste (t, 3.58);
token_afficher(t);

return 0;
}
