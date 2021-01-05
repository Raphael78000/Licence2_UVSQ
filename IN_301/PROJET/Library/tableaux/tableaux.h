
// Ici est la définition du type TAB utilisé pour stocker les données du texte afin qu'elles soient plus facilement exploitables

// En supposant qu'on traitera des textes de grandes tailles, sachant que taille_char, nb_mots et nb_lignes sont toujours positifs, 
// on fait le choix du type unsigned int pour nb_mots et nb_lignes et long unsigned int pour taille_char

struct tableaux { 
  long unsigned int taille_char;			   	   	 // Cette variable contiendra la taille du fichier en nombre de caractères 
  unsigned int nb_mots;                    			 // Cette variable contiendra le nombre de mots compris dans le texte
  int nb_lignes;                 			 		 // Cette variable contiendra le nombre de lignes du texte
  int max_mot;							  			 // Cette variable contiendra la longueur en lettres du mot le plus long du texte
  char* T;                    						 // T est un tableau de caractère qui contient l'intégralité du texte
  char** M;                      					 // M est un tableau de chaîne de caractères. Il contiendra tout les mots du texte
  int* L;                        					 // L est un tableau d'entiers. Il contiendra les indices du premier mot de la ligne i dans le texte stocké dans T
  int* C;											 // c est un tableua d'entiers. Il contiendra les indices du prochain mot à la fin de la ligne i parmi les mots stockés dans M
};
typedef struct tableaux* TAB;     // On définit TAB comme un pointeur vers un struct tableaux



// Voici la liste des macros utilisées dans le fichier tableaux.c

#define alphabet(x) (('a' <= (x) && (x) <= 'z')||( 'A' <= (x) && (x) <= 'Z' ))?1:0
// Ce que remplace la macro alphabet(x) renvoie VRAI si la variable est une lettre soit minuscule soit
// majuscule de l'alphabet latin dans la table ASCII, faux sinon

#define minuscule(x) ( 'A' <= (x) && (x) <= 'Z' )?( (x) + 0x20 ):(x)
// Ce que remplace la macro minuscule(x) renvoie la version minuscule de la lettre si elle est en majuscule,
// renvoie la lettre intacte sinon. Pour bien fonctionner, il faut que la variable renvoie VRAI quand elle
// est mise en argument de la macro alphabet(x)

#define scan(x) fscanf(f,"%c",&(x)) != EOF
// Ce que remplace la macro scan(x) est une condition qui est égale à FAUX quand on a atteint la fin du texte à scanner



// Voici les déclarations des fonctions contenues dans le fichier tableaux.c

TAB get_valeurs( char* fichier );

TAB init_tableaux ( char* fichier );

TAB remplir_tableaux( char* fichier, double* temps );

void afficher_tableaux_TL( TAB T );		

void afficher_tableaux_MC( TAB T );  



