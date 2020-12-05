#include <stdio.h>
#include <stdlib.h>
#include "exo_39.h"


void affn (int n) {
	int i;
	for (i=-n ; i<n ; i++) {
		printf(" %d",i);
	}
	printf("\n");
}


void affnrec (int n) {
	if (n==0) {
		printf("%d ",n);
		return;
	}
	printf("%d ",-n);
	affnrec(n-1);
	printf("%d ",n);
}

/*
affnrec(3)
	| -3
	| affnrec(2)
	|	| -2
	|	| affnrec(1)
	|	|	| -1
	|	|	|affnrec(0) | 0
	|	|	| 1
	|	| 2
	| 3
*/
