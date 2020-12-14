#include <stdlib.h>
#include <stdio.h>
#include "tableaux.h"
#include "ABR.h"
#include "AVL.h"
#include "recherche.h"
#include "chrono.h"

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


