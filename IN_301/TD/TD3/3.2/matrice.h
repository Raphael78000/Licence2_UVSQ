/*
  Structure :
  Nom  :  matrice
  Fct  :  structure definissant une matrice
*/

typedef struct matrice
  {
    int n;       /*---nombre de lignes---*/
    int m;       /*---nombre de colonnes---*/
    double* M;   /*---pointeur sur le premier élèment---*/
  } matrice_t;

/*
  Nom  :  m_alloc (a utiliser systematiquement apres
                   declaration ou allocation d'une matrice)
  Fct  :  alloue une matrice
  Entree  :  n nombre de lignes
             m nombre de colonnes
             (A) adresse de la matrice
*/

void m_alloc(const int n, const int m, matrice_t * const A);

/*
  Nom  :  m_free
  Fct  :  libere l'espace memoire occupe par une matrice
  Entree  :  (A) adresse de la matrice
*/

void m_free(matrice_t * const A);

/*
  Nom  :  m_somme
  Fct  :  effectue la somme de deux matrices
  Entree  :  (A) et (B) adresses matrices a additionner
             (C) adresse de la matrice resultat
*/

void m_somme(const matrice_t * const A, const matrice_t * const B, matrice_t * const C);

/*
  Nom  :  m_produit
  Fct  :  renvoie le produit de deux matrices
  Entree  :  (A) et (B) adresses des matrices a multiplier
             (C) adresse de la matrice resultat
*/

void m_produit(const matrice_t * const A, const matrice_t * const B, matrice_t * const C);
