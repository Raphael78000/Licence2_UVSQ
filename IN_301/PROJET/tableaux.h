
// Ici est la définition du type tableaux utilisé pour stocker les données du texte afin qu'elles soient plus facilement exploitables

// En supposant qu'on traitera des textes de grandes tailles, sachant que taille_char, nb_mots et nb_lignes sont toujours positifs, 
// on fait le choix du type unsigned int pour nb_mots et nb_lignes et long unsigned int pour taille_char

struct tableaux { 
  long unsigned int taille_char;			   	   	 // Cette variable contiendra la taille du fichier en nombre de caractères 
  unsigned int nb_mots;                    			 // Cette variable contiendra le nombre de mots compris dans le texte
  unsigned int nb_lignes;                 			 // Cette variable contiendra le nombre de lignes du texte
  int max_mot;							  			 // Cette variable contiendra la longueur en lettres du mot le plus long du texte
  char* T;                    						 // T est un tableau de caractère qui contient l'intégralité du texte
  char** M;                      					 // M est un tableau de chaîne de caractères. Il contiendra tout les mots du texte
  int* L;                        					 // L est un tableau d'entiers. Il contiendra les indices du premier mot de la ligne i dans le texte stocké dans T
  int* C;
};
typedef struct tableaux* TAB;     // On définit TAB comme un pointeur vers un struct tableaux


// Voici les déclarations des fonctions contenues dans le fichier tableaux.c

int alphabet ( char c );

TAB get_valeurs( char* fichier );

TAB init_tableaux ( char* fichier );

TAB remplir_tableaux( char* fichier );

void afficher_tableaux_TL( TAB T );		

void afficher_tableaux_MC( TAB T );    

void free_TL( TAB T );

void free_tableaux ( TAB T );


/* A faire : 
 - Comprendre pourquoi on commence à n_ligne = 2 
 */
