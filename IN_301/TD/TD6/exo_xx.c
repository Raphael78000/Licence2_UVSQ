#include <stdio.h>
#include <stdlib.h>

void affn (int n){
	for (int i=-n; i<=n;i++){
		printf("%d ",i);
	}
	printf("\n");
}

void affnrec (int n){
	printf("%d ",-n);
	if (n!=0){
		affnrec(n-1);
		printf("%d ",n);
	}
}

void affnrec2 (int n){
	affnrec(n);
	printf("\n");
}



