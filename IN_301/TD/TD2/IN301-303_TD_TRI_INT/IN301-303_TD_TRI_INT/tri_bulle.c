
#include "tabint.h"
#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

void tri_bulle_tabint (TABINT T){
	for (int i=T.N-2;i>=0;i--){
		for (int j=0;j<=i;j++){
			if(T.val[j+1]<T.val[j]){
				int t=T.val[j+1];
				T.val[j+1]=T.val[j];
				T.val[j]=t;}
			}
		}
}
struct stat stat_moy (int N, int NbFois){
	
	
	
	
int main() {
	
	// Le code ci-dessous est provisoire, juste pour faire marche l'enchainement du Makefile
	FILE *F;
	F = fopen("test_tri_bulle.data","w");
	fprintf(F,"   10           45.00           21.97\n");
 	fprintf(F,"   12           66.00           33.08\n");
 	fprintf(F,"   14           91.00           46.35\n");
 	fprintf(F,"   16          120.00           61.08\n");
 	fprintf(F,"   19          171.00           85.71\n");
 	fprintf(F,"   22          231.00          115.62\n");
 	fprintf(F,"   26          325.00          162.21\n");
	fclose(F);
	// Fin du code provisoire
	
	TABINT T;
	
	T=gen_alea_tabint(10,4);
	//aff_tabint(T);
	//desalloue_tabint(T);
	tri_bulle_tabint(T);
	aff_tabint(T);
	
	exit(0);
}
