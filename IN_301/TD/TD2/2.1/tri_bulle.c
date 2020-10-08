#include "tabint.h"
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

void tri_bulle_tabint (TABINT T){
	int t;
	for (int i=T.N-2;i>=0;i--){
		for (int j=0;j<=i;j++){
			if(T.val[j+1]<T.val[j]){
				t=T.val[j+1];
				T.val[j+1]=T.val[j];
				T.val[j]=t;}
			}
		}
}
	
	
	
	
int main() {
	
	TABINT T;
	
	T=gen_alea_tabint(10,4);
	tri_bulle_tabint(T);
	aff_tabint(T);
	if(verif_si_tableau_croissant(T)){
		printf("Le tableau trié\n");
		}
	desalloue_tabint(T);
	
	exit(0);
}
