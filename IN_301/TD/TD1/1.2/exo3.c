#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void ecrire (){
	int nombres;
	FILE *fichier = NULL;
	fichier = fopen ("nombres.data", "w");
	for (int i=0; i<10000; i++){
		nombres = rand ()% 1000 ;
		if (fichier != NULL){
			fprintf (fichier, "%6d\n", nombres);
			}
		}
		fclose(fichier);
}

int main(){
	srand (getpid());
	ecrire();
	printf ("C'est fait\n");
}

