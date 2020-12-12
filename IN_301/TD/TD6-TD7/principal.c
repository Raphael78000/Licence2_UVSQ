#include <stdio.h>
#include <stdlib.h>
#include "exo_39.h"
#include "exo_40.h"
#include "exo_41.h"
#include "exo_42.h"
#include "exo_43.h"
#include "exo_44-45.h"
#include "exo_46-47.h"
#include "exo_48.h"


int main() {
	printf("-----Exercice 39-----\n");
	affn(5);

	affnrec(4); printf("\n");
	affnrec(5); printf("\n");

	printf("-----Exercice 40-----\n");
	afftailletype();

	printf("-----Exercice 41-----\n");
	compadeux();

	printf("-----Exercice 42-----\n");
	compadeux2();

	printf("-----Exercice 43-----\n");
	decalage();

	printf("-----Exercice 44-45-----\n");
	bitabit();

	printf("-----Exercice 46-47-----\n");
	precision();

	printf("-----Exercice 48-----\n");
	macros();

	return 0;
}
