
// Dans le tas les indices commencent à 1.
// La case du tableau val d'indice 0 n'est pas utilisée
struct tas {
	int taille; // Le nombre d'éléments du tas
	int *val;   // Le tableau des valeurs
};


typedef struct tas TAS;

// Initialise un tas vide qui peut stocker jusqu'à N valeurs
TAS tas_creer(int N);

// Désalloue la mémoire
void tas_vider(TAS t);

// Ajoute la valeur n dans le tas
TAS tas_inserer(TAS t, int n);

// Supprimer la valeur max du tas
TAS tas_supprimer(TAS t);

// Tri par tas
TAS tas_trier(TAS t);

// Afficher
void tas_afficher(TAS t);

// Trie le tableau tt de taille N
// avec un tri par tas
void tri_par_tas(int *tt, int N);
