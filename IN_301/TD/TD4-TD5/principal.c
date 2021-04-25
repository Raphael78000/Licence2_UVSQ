#include <stdio.h>
#include <stdlib.h>
#include "ea.h"
#include "token.h"
#include "token_ea.h"


int main() {
	char *s = "(  2.765 +  (  3.1415 * 4  ))";

	TOKEN t;
	t = token_creer_liste (s);
	token_afficher(t);
	
	EA e;
	e = token_to_EA(t);
	ea_afficher(e);
	printf("\n");
	printf("%s = %f\n",s,ea_evaluer(e));

	return 0;
}
