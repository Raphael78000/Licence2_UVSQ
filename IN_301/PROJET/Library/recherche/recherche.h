
void mode_recherche ( ARBRE A, TAB T, int argc, char** argv, double* temps);

ARBRE recherche ( ARBRE A, char* s);

void afficher_recherche ( ARBRE A, char* mot, TAB T );

int compamots( char* mot1, char* mot2 );

void free_liste( LISTE L );

void free_arbre ( ARBRE A );

void free_all ( TAB T, ARBRE A, double* temps);
