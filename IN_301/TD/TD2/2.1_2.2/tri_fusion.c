#include "tabint.h"
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

void fusionner (TABINT T, int deb, int mil, int fin){
	int *temp = malloc(sizeof(int)*(fin -deb));
	int i = deb;
	int j = mil;
	int k = 0;
	while(k < fin - deb){
		if(i == mil){
			for(;j<fin;j++){
				temp[k] = T.val[j];
				NBECH++;
				k++;	
			}
			break;
			NBCOMP++;
		}
		if(j == fin){
			for(;i<mil;i++){
				temp[k] = T.val[i];
				NBECH++;
				k++;	
			}
			break;
			NBCOMP++;
		}
		if(T.val[i] < T.val[j]){
			temp[k] =T.val[i];
			NBECH++;
			i++;
			NBCOMP++;
		}
		else{
			temp[k] = T.val[j];
			NBECH++;
			j++;	
		}
		k++;
	}
	for(i = 0; i < fin - deb; i++){
		T.val[i + deb] = temp[i];
	}
	free(temp);
}

void tri_fusion(TABINT T, int deb, int fin){
	if((fin - deb) > 1){
		tri_fusion(T,deb,(fin + deb)/2);
		tri_fusion(T,(fin + deb)/2,fin);
		fusionner(T,deb,(fin + deb)/2, fin);
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
