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
				k++;	
			}
			break;
		}
		if(j == fin){
			for(;i<mil;i++){
				temp[k] = T.val[i];
				k++;	
			}
			break;
		}
		if(T.val[i] < T.val[j]){
			temp[k] =T.val[i];
			i++;
		}
		else{
			temp[k] = T.val[j];
			j++;	
		}
		k++;
	}
	for(i = 0; i < fin - deb; i++){//cette boucle devrait etre remplacé par un appel à memcpy
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

int main() {
	
	TABINT T;
	
	T=gen_alea_tabint(10,4);
	aff_tabint(T);
	printf("\n\n");
	tri_fusion_tabint(T);
	aff_tabint(T);
	if(verif_si_tableau_croissant(T)){
		printf("Le tableau est trié\n");
		}
	desalloue_tabint(T);
	
	exit(0);
}
