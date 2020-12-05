#include <stdio.h>
#include <stdlib.h>
#include "exo_42.h"

void compadeux2() {
	int i;
	char c = 0;
	for (i=1 ; i<=307 ; i++) {
		printf(" %4d",c);
		c = c+1;
		if (i%10==0) printf("\n");
	}
	printf("\n##\n");
	unsigned char d = 0;
	for (i=1 ; i<=307 ; i++) {
		printf(" %4u",d);
		d = d+1;
		if (i%10==0) printf("\n");
	}
	printf("\n##\n");

	for (d=32 ; d<=127 ; d++) {
		printf("%4u %4o %4x #%c#\n",d,d,d,d);
	}
	d = ' ';
	printf("Espace : %4u %4o %4x #%c#\n",d,d,d,d);
		
}

