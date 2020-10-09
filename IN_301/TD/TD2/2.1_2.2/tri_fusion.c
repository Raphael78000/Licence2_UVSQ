#include "tabint.h"
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

void fusionner (TABINT T, int deb, int mil, int fin){
	int *tab=malloc(sizeof(int)*(fin+1));
	int i,k,j;
	i=deb;k=deb;j=mil+1;
	
	while ((i<=mil) && (j<=fin)){
		if (T.val[i]<T.val[j]){
			tab[k]=T.val[i];
			i=i+1;
			NBECH++;
		}
		else{
			tab[k]=T.val[j];
			j=j+1;
			NBECH++;
		}
		k=k+1;
		NBCOMP++;
	}
	while (i<=mil){
		NBCOMP++;
		tab[k]=T.val[i];
		NBECH++;
		i=i+1;
		k=k+1;
	}
	while (j<=fin){
		tab[k]=T.val[j];
		NBECH++;
		j=j+1;
		k=k+1;
		NBCOMP++;
	}
	 for (int a=0;a<fin;a++){
		 T.val[a]=tab[a];
		 NBECH++;
	 }
	 free(tab);
 }

void tri_fusion(TABINT T, int deb, int fin){
	if(deb<fin){
		int mil=((deb+fin)/2);
		tri_fusion(T,deb,mil);
		tri_fusion(T,mil+1,fin);
		fusionner(T,deb,mil, fin);
	}
}

void tri_fusion_tabint(TABINT T){
	tri_fusion(T,0,T.N);
}

struct stat stat_moy (int N, int NbFois){
	TABINT T;
	NBCOMP=0;
	NBECH=0;
	
	for (int i=0;i<NbFois;i++){
		T=gen_alea_tabint(N,100);
		tri_fusion_tabint(T);
		desalloue_tabint(T);
	}
	struct stat s;
	s.nb_moy_comp = (float)NBCOMP/NbFois;
	s.nb_moy_ech = (float)NBECH/NbFois;
	return s;
}

void genere_stat(){
	struct stat s;
	FILE * F = fopen("test_tri_fusion.data","w");
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
	T=gen_alea_tabint(dimension_tab,4);
	tri_fusion_tabint(T);
	desalloue_tabint(T);
	
	exit(0);
}
*/
