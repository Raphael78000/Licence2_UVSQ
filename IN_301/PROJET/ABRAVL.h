struct liste {
	unsigned int ligne;
	struct liste* suiv;
};
typedef struct liste* LISTE;

struct noeud {
	char* mot;
	short occ;
	struct noeud* parent;
	struct noeud* sag;
	struct noeud* sad;
	LISTE num_ligne;
};
typedef struct noeud* ARBRE;


ARBRE init_noeud ( char* s, int ligne );

LISTE init_liste ( int ligne );

LISTE inserer_ligne ( LISTE L, int ligne );

ARBRE inserer_noeud ( ARBRE A, ARBRE N );

void afficher_arbre ( ARBRE A );

void free_liste ( LISTE L );

void free_arbre ( ARBRE A );

int equilibre (ARBRE A);

int hauteur (ARBRE A);

int max (int a, int b);

LISTE ligne_mot (TAB A, char *s);

void afficher_liste (LISTE a);

// Proposition : Si le fichier ABRAVL.c devient trop long, on le divisera en fichier ABR.c et AVL.c
