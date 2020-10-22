#include "matrice.h"

/*
  Nom  :  m_alloc (a utiliser systematiquement apres
                   declaration ou allocation d'une matrice)
  Fct  :  alloue une matrice
  Entree  :  n nombre de lignes
             m nombre de colonnes
             (A) adresse de la matrice
*/

void m_alloc(int n,int m,matrice_t* A)
{
  A.n = n;
  A.m = m;
  A.M = (double*)malloc(n*m*sizeof(double));
}

/*
  Nom  :  m_free
  Fct  :  libere l'espace memoire occupe par une matrice
  Entree  :  (A) adresse de la matrice
*/

void m_free(matrice_t* A)
{
  free(A.M);
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
  m_alloc(A.n,A.m,C);
  for(i=1 ; i<=C->n ; i++)
  {
    for(j=1 ; j<=C->m ; j++)
    {
      *m_elem(C,i,j)=(*m_elem(A,i,j))+(*m_elem(B,i,j));
    }
  }
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
  m_alloc(A.n,B.m,C);
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
