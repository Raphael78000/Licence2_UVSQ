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
	
	
	
	
int main(int argc,char **argv) {
	
	TABINT T;
	
	int dimension_tab=atoi(argv[1]);
	T=gen_alea_tabint(dimension_tab,4);
	tri_bulle_tabint(T);
	desalloue_tabint(T);
	
	exit(0);
}
