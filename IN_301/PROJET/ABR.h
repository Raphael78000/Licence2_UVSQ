
// Ici est la définition du type LISTE qui est utilisé pour stocker les numéros de ligne d'un mot
struct liste {
	unsigned int ligne;			// La variable ligne stocke le numéro de ligne d'un mot. Elle est de type unsigned int car un numéro de ligne est toujours positif et peut être grand si le texte l'est aussi 
	struct liste* suiv;			// Le pointeur suiv pointe vers un autre élément struct liste qui va être exploité comme l'élément qui suit 
};
typedef struct liste* LISTE;	// On définit LISTE comme un pointeur vers une structure liste


// Ici est la définition du type ARBRE qui est utilisé pour stocker les mots de façon à avoir un arbre AVL
struct noeud {
	char* mot;				// La variable mot prend une chaîne de caractère en valeur. Elle stockera le mot du noeud
	int occ;				// La variable occ représente le nombre d'occurence d'un mot d'un texte
	struct noeud* sag;		// Le pointeur sag pointe vers un autre élément struct noeud qui va être exploité comme son fils gauche/son sous-arbre gauche
	struct noeud* sad;		// Le pointeur sad pointe vers un autre élément struct noeud qui va être exploité comme son fils droit/son sous-arbre droit
	LISTE num_ligne;		// L'élément num_ligne de type LISTE nous servira un lister les numéros de ligne où le mot apparaît
};
typedef struct noeud* ARBRE;	// On définit ARBRE comme un pointeur vers une structure noeud


// Voici les déclarations des fonctions contenues dans le fichier ABR.c

LISTE init_liste ( int ligne );			
		
LISTE inserer_ligne ( LISTE L, int ligne );			

ARBRE init_noeud ( char* s, int ligne );			

ARBRE inserer_noeud ( ARBRE A, TAB T, int mot, int ligne );	

void afficher_arbre ( ARBRE A );		

void afficher_noeud ( ARBRE A );			
		
ARBRE TAB_to_ARBRE (TAB T, double* temps);			
