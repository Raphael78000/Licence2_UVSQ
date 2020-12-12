#include <stdio.h>
#include <stdlib.h>
#include "exo_41.h"

void compadeux() {
	int a = -1;
	printf(" a avec %%d : %d\n",a);
	printf(" a avec %%u : %u\n\n",a);


	a = 2147483647;
	printf(" a avec %%d : %d\n",a);
	a = a+1;
	printf(" a avec %%d : %d\n",a);
	a = a+1;
	printf(" a avec %%d : %d\n\n",a);

	a = 2147483647;
	printf(" a avec %%u : %u\n",a);
	a = a+1;
	printf(" a avec %%u : %u\n",a);
	a = a+1;
	printf(" a avec %%u : %u\n\n",a);
}
