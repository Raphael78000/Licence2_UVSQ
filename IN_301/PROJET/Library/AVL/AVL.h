

// Voici la macro utilisée dans le fichier AVL.c

#define max(x,y) (((x)<=(y))?(y):(x))
//La fonction max renvoie la plus grande valeur des deux mises en argument


// Voici les déclarations des fonctions contenues dans le fichier AVL.c

int hauteur ( ARBRE A );	

ARBRE rotation_droite ( ARBRE A );	

ARBRE rotation_gauche ( ARBRE A );	

ARBRE desequilibre ( ARBRE A );		

int AVL ( ARBRE A );		

