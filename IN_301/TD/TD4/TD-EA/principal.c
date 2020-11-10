#include <stdio.h>
#include <stdlib.h>
#include "ea.h"

int main(){

	EA e,e1,e2;
e1 = ea_creer_valeur(12.3);
e2 = ea_creer_valeur(4.56);
e = ea_creer_operation('+',e1,e2);
printf("%f\n",ea_evaluer(e));

return 0;
}
