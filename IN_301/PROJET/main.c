#include <stdlib.h>
#include <stdio.h>
#include "tableaux.h"
#include "ABRAVL.h"

int main ( int argc, char** argv )
{
	TAB T;								// Déclaration d'une variable T de type TAB.
	LISTE a;
	char s[]="project";

	T = remplir_tableaux(argv[1]);		// Remplissage de T avec les valeurs du fichier passé en argument. Ici le nom du fichier est la deuxième chaîne de caractère après "./dico" sur la ligne de commande.
/*	afficher_tableaux_TL(T);			// Afficher le contenu du texte en utilisant les tableaux T et L
	afficher_tableaux_MC(T);    		// Afficher le contenu du texte en utilisant les tableaux M et C
	free_tableaux(T);*/					// Libérer l'espace occupé par la variable T
	a=ligne_mot(T,s);
	afficher_liste(a);
	return 0;
}
