#include "tabint.h"
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

void tri_bulle_tabint (TABINT T){
	int t;
	for (int i=T.N-2;i>=0;i--){
		NBCOMP++;
		for (int j=0;j<=i;j++){
			if(T.val[j+1]<T.val[j]){
				NBECH++;
				t=T.val[j+1];
				T.val[j+1]=T.val[j];
				T.val[j]=t;}
			}
		}
}
	
struct stat stat_moy (int N, int NbFois){
	TABINT T;
	NBCOMP=0;
	NBECH=0;
	
	for (int i=0;i<NbFois;i++){
		T=gen_alea_tabint(N,100);
		tri_bulle_tabint(T);
		desalloue_tabint(T);
	}
	struct stat s;
	s.nb_moy_comp = (float)NBCOMP/NbFois;
	s.nb_moy_ech = (float)NBECH/NbFois;
	return s;
}

void genere_stat(){
	struct stat s;
	FILE * F = fopen("test_tri_bulle.data","w");
	for(int i = 10; i < 1000; i*=1.2){
		s = stat_moy(i,10000);
		fprintf(F,"%d %f %f\n",i,s.nb_moy_comp,s.nb_moy_ech);
	}
	fclose(F);
}

int main(){
	
	genere_stat();
	return 0;
}
	
	
/*Partie Exercice 13 d),e)
int main(int argc,char **argv) {
	
	TABINT T;
	
	int dimension_tab=atoi(argv[1]);
	
	
	exit(0);
}
*/
