#include "matrice.h"

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

void m_alloc(const int n, const int m, matrice_t * const A)
{
  A->n = n;
  A->m = m;
  A->M = (double*)malloc(n*m*sizeof(double));
}

/*
  Nom  :  m_elem
  Fct  :  retourne l'adresse de l'element d'une matrice
  Entree  :  (A) adresse de la matrice
             i indice de la ligne
             j indice de la colonne
  Sortie  :  adresse de l'element correspondant
*/

double * m_elem(const matrice_t * const A, const int i,const int j)
{
  return (A->M+(i-1)+A->n*(j-1));
}

/*
  Nom  :  m_free
  Fct  :  libere l'espace memoire occupe par une matrice
  Entree  :  (A) adresse de la matrice
*/

void m_free(matrice_t * const A)
{
  free(A->M);
}


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

void m_copy(const matrice_t * const A, matrice_t * const B)
{
  int k;
  m_free(B);
  m_alloc(A->n,A->m,B);
  for (k=0 ; k<(A->n)*(A->m) ; k++)
  {
    B->M[k]=A->M[k];
  }
}

/*
  Nom  :  m_somme
  Fct  :  effectue la somme de deux matrices
  Entree  :  (A) et (B) adresses des matrices a additionner
             (C) adresse de la matrice resultat
*/

void m_somme(const matrice_t * const A, const matrice_t * const B, matrice_t * const C)
{
  int i,j;
  m_free(C);
  m_alloc(A->n,A->m,C);
  for(i=1 ; i<=C->n ; i++)
  {
    for(j=1 ; j<=C->m ; j++)
    {
      *m_elem(C,i,j)=(*m_elem(A,i,j))+(*m_elem(B,i,j));
    }
  }
}

/*
  Nom  :  m_somme_pond
  Fct  :  effectue une combinaison lineaire de deux matrices
  Entree  :  a et b coefficients de ponderation
             (A) et (B) adresses des matrices a additionner
             (C) adresse de la matrice resultat
*/

void m_somme_pond(const double a, const double b, const matrice_t * const A, const matrice_t * const B, matrice_t * const C)
{
  int i,j;
  m_free(C);
  m_alloc(A->n,A->m,C);
  for(i=1 ; i<=C->n ; i++)
  {
    for(j=1 ; j<=C->m ; j++)
    {
      *m_elem(C,i,j)=a*(*m_elem(A,i,j))+b*(*m_elem(B,i,j));
    }
  }
}

/*
  Nom  :  m_ligne
  Fct  :  extrait une ligne d'une matrice
  Entree  :  (A) adresse de la matrice dont on souhaite extraire une ligne
             l indice de la ligne a extraire
             (C) adresse de la matrice resultat
*/

void m_ligne(const matrice_t * const A, const int l, matrice_t * const C)
{
  int j;
  m_free(C);
  m_alloc(1,A->m,C);
  for(j=1;j<=C->m;j++)
  {
    *m_elem(C,1,j)=*m_elem(A,l,j);
  }
}

/*
  Nom  :  m_colonne
  Fct  :  extrait une colonne d'une matrice
  Entree  :  (A) adresse de la matrice dont on souhaite extraire une colonne
             c indice de la colonne a extraire
             (C) adresse de la matrice resultat
*/

void m_colonne(const matrice_t * const A, const int c, matrice_t * const C)
{
  int i;
  m_free(C);
  m_alloc(A->n,1,C);
  for(i=1 ; i<=C->n ; i++)
  {
    *m_elem(C,i,1)=*m_elem(A,i,c);
  }
}

/*
  Nom  :  m_produit_scal
  Fct  :  renvoie le produit scalaire entre un vecteur ligne et un vecteur colonne
  Entree  :  (A) adresse de la matrice ligne
             (B) adresse de la matrice colonne
  Sortie  :  produit scalaire
*/

double m_produit_scal(const matrice_t * const A, const matrice_t * const B)
{
  double p=0;
  int k;
  for(k=1 ; k<=A->m ; k++)
  {
    p=p+(*m_elem(A,1,k))*(*m_elem(B,k,1));
  }
  return p;
}

/*
  Nom  :  m_produit
  Fct  :  renvoie le produit de deux matrices
  Entree  :  (A) et (B) adresses des matrices a multiplier
             (C) adresse de la matrice resultat
*/

void m_produit(const matrice_t * const A, const matrice_t * const B, matrice_t * const C)
{
  double p;
  int i,j,k;
  m_free(C);
  m_alloc(A->n,B->m,C);
  for(i=1 ; i<=A->n ; i++)
  {
    for(j=1 ; j<=B->m ; j++)
    {
      p=0;
      for(k=1 ; k<=A->m ; k++)
      {
        p=p+(*m_elem(A,i,k))*(*m_elem(B,k,j));
      }
      *m_elem(C,i,j)=p;
    }
  }
}

/*
  Nom  :  m_reshape
  Fct  :  renvoie une matrice remplie par colonne avec les valeurs d'un vecteur
  Entree  :  n nombre de lignes
             m nombre de colonnes
             (V) vecteur fournissant les valeurs
             (C) adresse de la matrice resultat
*/

void m_reshape(const int n, const int m, const double * const V, matrice_t * const C)
{
  int k;
  m_free(C);
  m_alloc(n,m,C);
  for(k=0 ; k<(C->n * C->m) ; k++)
  {
    *(C->M+k)=V[k];
  }
}


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

void m_unite(const int k, matrice_t * C)
{
  int i,j;
  m_free(C);
  m_alloc(k,k,C);
  for(i=1 ; i<=C->n ; i++)
  {
    for(j=1 ; j<=C->m ; j++)
    {
      if(i==j)
      {
        *m_elem(C,i,j)=1;
      }
      else
      {
        *m_elem(C,i,j)=0;
      }
    }
  }
}

/*
  Nom  :  m_nulle
  Fct  :  renvoie une matrice nulle
  Entree  :  k taille de la matrice
             (C) adresse de la matrice resultat
*/

void m_nulle(const int k, matrice_t * C)
{
  int i,j;
  m_free(C);
  m_alloc(k,k,C);
  for(i=1;i<=C->n;i++)
  {
    for(j=1;j<=C->m;j++)
    {
      *m_elem(C,i,j)=0;
    }
  }
}

/*
  Nom  :  m_val
  Fct  :  renvoie une matrice initialisee a une valeur donnee
  Entree  :  k taille de la matrice
             v valeur des elements de la matrice
             (C) adresse de la matrice resultat
*/

void m_val(const int k, const double v, matrice_t * C)
{
  int i,j;
  m_free(C);
  m_alloc(k,k,C);
  for(i=1 ; i<=C->n ; i++)
  {
    for(j=1 ; j<=C->m ; j++)
    {
      *m_elem(C,i,j)=v;
    }
  }
}

/*
  Nom  :  m_hilbert
  Fct  :  renvoie une matrice de Hilbert
  Entree  :  k taille de la matrice
             (C) adresse de la matrice resultat
*/

void m_hilbert(const int k, matrice_t * C)
{
  int i,j;
  m_free(C);
  m_alloc(k,k,C);
  for(i=1;i<=C->n;i++)
  {
    for(j=1;j<=C->m;j++)
    {
      *m_elem(C,i,j)=1/(double)(i+j-1);
    }
  }
}

