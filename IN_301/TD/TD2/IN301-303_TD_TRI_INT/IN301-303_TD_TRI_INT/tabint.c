#include "tabint.h"
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>


// #####
// 1. Allocation, désallocation, génération aléatoire
//    et affichage de tableaux
// #####
TABINT alloue_tabint (int N) {
	TABINT T;
	T.N = N;
	T.val = malloc(N*sizeof(int));
	return T;
}
TABINT desalloue_tabint (TABINT T) {
	free(T.val);
	T.N=0;
	return T;
}

TABINT gen_alea_tabint (int N, int K) {
	TABINT T;
	T = alloue_tabint(N);
	
	for (int i=0;i<N;i++){
		T.val[i]=rand()%K;
	}
	
	return T;
}

TABINT sup_tabint (TABINT T) {
	return T;
}

void aff_tabint (TABINT T) {
	for (int i=0;i<T.N;i++){
		printf("%d\n",T.val[i]);
	}
}

int verif_si_tableau_croissant (TABINT T) {
	
for (int i=0;i<T.N;i++){
	if(T.val[i]>T.val[i+1]){
		return 0;}
	}
	return 1;
}


