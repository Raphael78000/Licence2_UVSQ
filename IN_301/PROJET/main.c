#include <stdlib.h>
#include <stdio.h>
#include "./Library/tableaux/tableaux.h"
#include "./Library/ABR/ABR.h"
#include "./Library/AVL/AVL.h"
#include "./Library/recherche/recherche.h"
#include "./Library/chrono/chrono.h"

int main ( int argc, char** argv )
{
	double temps = 0;
	
	TAB T = remplir_tableaux(argv[1], &temps);	
	
	ARBRE A = TAB_to_ARBRE(T, &temps);
	
	mode_recherche ( A, T, argc, argv, &temps);	
	
	free_all(T, A, &temps);	
	
	FILE* f = fopen ("Resultat.txt", "a");
	if ( !f )
	{
		printf("Il y a eu un problème avec l'ouverture du fichier Resultat.txt\n");
		exit(1);
	}
	fprintf(f, "========>    L'éxecution du programme a duré %f millisecondes \n\n", temps);
	fclose(f);
	
	return 0; 
}
