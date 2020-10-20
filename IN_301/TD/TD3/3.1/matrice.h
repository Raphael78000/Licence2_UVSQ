#ifndef _matrice_h_
#define _matrice_h_

/*---------------- STRUCTURE DE MATRICE.C ------------------------------------*/

/*
  Structure :
  Nom  :  matrice
  Fct  :  structure definissant une matrice
*/

typedef struct matrice
  {
    int n;       /*---nombre de lignes---*/
    int m;       /*---nombre de colonnes---*/
    double * M;  /*---pointeur sur le premier element---*/
  } matrice_t;


/*---------------- FONCTIONS DE MATRICE.C ------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   Fonctions de gestion de la structure                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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
  Nom  :  m_elem
  Fct  :  retourne l'adresse de l'element d'une matrice
  Entree  :  (A) adresse de la matrice
             i indice de la ligne
             j indice de la colonne
  Sortie  :  adresse de l'element correspondant
*/

double * m_elem(const matrice_t * const A, const int i, const int j);

/*
  Nom  :  m_free
  Fct  :  libere l'espace memoire occupe par une matrice
  Entree  :  (A) adresse de la matrice
*/

void m_free(matrice_t * const A);


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   Fonctions basiques                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
  Nom  :  m_copy
  Fct  :  retourne l'adresse de l'element d'une matrice
  Entree  :  (A) adresse de la matrice a copier
             (B) adresse de la matrice resultat
*/

void m_copy(const matrice_t * const A, matrice_t * const B);

/*
  Nom  :  m_somme
  Fct  :  effectue la somme de deux matrices
  Entree  :  (A) et (B) adresses matrices a additionner
             (C) adresse de la matrice resultat
*/

void m_somme(const matrice_t * const A, const matrice_t * const B, matrice_t * const C);

/*
  Nom  :  m_somme_pond
  Fct  :  effectue une combinaison lineaire de deux matrices
  Entree  :  a et b coefficients de ponderation
             (A) et (B) adresses des matrices a additionner
             (C) adresse de la matrice resultat
*/

void m_somme_pond(const double a, const double b, const matrice_t * const A, const matrice_t * const B, matrice_t * const C);

/*
  Nom  :  m_ligne
  Fct  :  extrait une ligne d'une matrice
  Entree  :  (A) adresse de la matrice dont on souhaite extraire une ligne
             l indice de la ligne a extraire
             (C) adresse de la matrice resultat
*/

void m_ligne(const matrice_t * const A, const int l, matrice_t * const C);

/*
  Nom  :  m_colonne
  Fct  :  extrait une colonne d'une matrice
  Entree  :  (A) adresse de la matrice dont on souhaite extraire une colonne
             c indice de la colonne a extraire
             (C) adresse de la matrice resultat
*/

void m_colonne(const matrice_t * const A, const int c, matrice_t * const C);

/*
  Nom  :  m_produit_scal
  Fct  :  renvoie le produit scalaire entre un vecteur ligne et un vecteur colonne
  Entree  :  (A) adresse d'une matrice ligne
             (B) adresse d'une matrice colonne
  Sortie  :  produit scalaire
*/

double m_produit_scal(const matrice_t * const A, const matrice_t * const B);

/*
  Nom  :  m_produit
  Fct  :  renvoie le produit de deux matrices
  Entree  :  (A) et (B) adresses des matrices a multiplier
             (C) adresse de la matrice resultat
*/

void m_produit(const matrice_t * const A, const matrice_t * const B, matrice_t * const C);

/*
  Nom  :  m_reshape
  Fct  :  renvoie une matrice remplie par colonne avec les valeurs d'un vecteur
  Entree  :  n nombre de lignes
             m nombre de colonnes
             (V) vecteur fournissant les valeurs
             (C) adresse de la matrice resultat
*/

void m_reshape(const int n, const int m, const double * const V, matrice_t * const C);


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   Fonctions de construction de matrices particulières                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
  Nom  :  m_unite
  Fct  :  renvoie une matrice unite
  Entree  :  k taille de la matrice
             (C) adresse de la matrice resultat
*/

void m_unite(const int k, matrice_t * C);

/*
  Nom  :  m_nulle
  Fct  :  renvoie une matrice nulle
  Entree  :  k taille de la matrice
             (C) adresse de la matrice resultat
*/

void m_nulle(const int k, matrice_t * C);

/*
  Nom  :  m_val
  Fct  :  renvoie une matrice initialisee a une valeur donnee
  Entree  :  k taille de la matrice
             v valeur des elements de la matrice
             (C) adresse de la matrice resultat
*/

void m_val(const int k, const double v, matrice_t * C);

/*
  Nom  :  m_hilbert
  Fct  :  renvoie une matrice de Hilbert
  Entree  :  k taille de la matrice
             (C) adresse de la matrice resultat
*/

void m_hilbert(const int k, matrice_t * C);


#endif
