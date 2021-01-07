#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tas.h"

#define NN 30

int * tableau_aleatoire (int N, int MAX) {
	int *t;
	t = malloc(N*sizeof(int));
	if (!t) exit(2);
	int i;
	srandom(getpid());
	for (i=0; i<N ; i++) 
		t[i] = random()%MAX;
	return t;
}

void tableau_afficher(int *t, int N) {
	int i;
	printf("t   :");
	for (i=0 ; i<N ; i++) printf(" %3d",t[i]);
	printf("\n");
}

void tableau_verifier(int *t, int N) {
	int i;
	for (i=0 ; i<N-1 ; i++) 
		if (t[i]>t[i+1]) {
			printf("Tableau t non trié : t[%d]=%3d > %3d=t[%d].\n",i,t[i],t[i+1],i+1);
			return;
		}
	printf("Tableau t trié.\n");
}

int main() {
	int *t;
	printf("TRI PAR TAS d'un tableau t de %d valeurs aléatoires\n",NN);
	t = tableau_aleatoire(NN,1000);
	tableau_afficher(t,NN);
//	tableau_verifier(t,NN);
	tri_par_tas(t,NN);
	tableau_afficher(t,NN);
	tableau_verifier(t,NN);
	return 0;
}
