#include <stdio.h>
#include <stdlib.h>
#include "tas.h"

#define swap(x,y) ( (x)^=(y) , (y)^=(x), (x)^=(y))

// Échange les cases i et j du tas t
void tas_echange(TAS t, int i, int j) {
	swap(t.val[i],t.val[j]);
}

//#define DEBUG_INS
//#define DEBUG_SUP

// Initialise un tas vide
TAS tas_creer(int N) {
	TAS t;
	t.taille = 0;
	t.val = malloc((N+1)*sizeof(int));
			// Comme les indices utiles comment à 1
			// on alloue TAILLE_MAX + 1 cases pour 
			// stocker TAILLE_MAX valeurs
	if (!(t.val)) {
		fprintf(stderr,"PB malloc\n");
		exit(2);
	}
	return t;
}

// Désalloue la mémoire
void tas_vider(TAS t) {
	free(t.val);
}

// Vérification que c'est bien un tas valide
int tas_valide (TAS t) {
	printf("VERIF\n");
	int i;
	for (i=2 ; i<=t.taille ; i++) {
		if (t.val[i]>t.val[i/2]) {
			printf("Tas NON valide\n");
			return 0;
		}
	}
	printf("Tas valide\n");
	return 1;
}

// Ajoute la valeur n dans le tas
// Complexité en O(log(n))
TAS tas_inserer(TAS t, int n) {
//	if (t.taille>=TAILLE_MAX) {
//		fprintf(stderr,"Tas plein (pb implem)\n");
//		fprintf(stderr,"insertion on faite\n");
//		return t;
//	}
	(t.taille)++;
	int i; // case de la nouvelle valeur
	i = t.taille;
	t.val[i] = n;
	// On remonte la valeur insérée dans l'arbre
	while ((i>1) && (t.val[i/2]<t.val[i])) {
		tas_echange(t,i/2,i);
		i = i/2;
	}
#ifdef DEBUG_INS
	if (!tas_valide(t)) {
		fprintf(stderr,"Pb tas non valide\n");
		exit(4);
	}
#endif
	return t;
}

// Renvoie l'indice du fils max de i
int maxfils (TAS t, int i) {
	// Cas d'un seul fils
	if (2*i==t.taille) return t.taille; 
	// Renvoie 2*i ou 2*i+1
	return 2*i + (t.val[2*i+1]>t.val[2*i]);
}

// Supprimer la valeur n dans le tas
// Complexité en O(h), comme le tas est un arbre parfait
// h = log(n) et donc complexité en O(log(n))
TAS tas_supprimer(TAS t) {
	tas_echange(t,1,t.taille);
	(t.taille)--;
	int i = 1;
	int mi = maxfils(t,1);
	while ( (2*i<=t.taille) && (t.val[i]<t.val[mi])) {
		tas_echange(t,i,mi);
		i  = mi;
		mi = maxfils(t,i);
	}


#ifdef DEBUG_SUP
	if (!tas_valide(t)) {
		fprintf(stderr,"Pb tas non valide\n");
		exit(4);
	}
#endif
	return t;
}

// Afficher
void tas_afficher(TAS t) {
	int i;
	printf("TAS :");
	for (i=1 ; i<=t.taille ; i++) {
		printf(" %3d",t.val[i]);
	}
	printf("\n");
}

// Tri par tas
// Complexité en O(n*log(n))
// Car on répète n fois tas_inserer(tt) tas_supprimer(tt)
// qui sont de complexité O(log(n))
// Attention à la fin ce n'est plus un tas, c'est un tableau
void tri_par_tas(int *tt, int N) {
	int i;
	TAS t = tas_creer(N);
	for (i=0 ; i<N ; i++) t = tas_inserer(t,tt[i]);
	tas_afficher(t);
	for (i=0 ; i<N ; i++) t = tas_supprimer(t);
	t.taille = N; tas_afficher(t);
	for (i=0 ; i<N ; i++) tt[i] = t.val[i];
	tas_vider(t);
}
