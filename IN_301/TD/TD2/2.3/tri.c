#include "tableau.h"
#include <string.h>

//associe à chaque caractere un indice dans le tableau des frequences
//les caracteres possible sont les caracteres alphabetiques en minuscules 
//et le caractere de fin de chaine '\0' qui sert aussi pour marquer l'absence de lettre
int indice(char c){
	return (c == '\0') ? 0 : c - 'a' + 1;
}


//tri le tableau  selon la composante i
void tri_base_indice(Tableau t, int i){
	int *frequences = calloc(sizeof(int),27);//calloc alloue la memoire et intialise a 0
	for(int j = 0; j < t.n; j++){//calcul des fréquences des lettres apparaissant
								 // en position i dans les mots de t
		frequences[indice(t.tab[j][i])]++;
	}
	int *frequences_cumulees = calloc(sizeof(int),27);
	for(int j=1; j< 27; j++){//calcul des fréquences cumulées
		frequences_cumulees[j] = frequences_cumulees[j-1] + frequences[j-1];
	}
	char **temp = malloc(sizeof(char*)*t.n);
	int pos;
	for(int j = 0; j < t.n; j++){
		pos = indice(t.tab[j][i]);
		temp[frequences_cumulees[pos]] = t.tab[j];
		frequences_cumulees[pos]++;
	}
	for(int j = 0; j < t.n; j++){//recopie de temp dans tab, devrait utiliser memcpy
		t.tab[j] = temp[j];
	}
	//libération des trois tableaux temporaires
	//pour améliorer les performances, il faudrait les allouer une fois pour toute
	free(temp);
	free(frequences);
	free(frequences_cumulees);
}



 
//tri par base 
void tri_base(Tableau t){
  int i;
  for(i=t.taille-1; i>=0; i--)
    tri_base_indice(t, i);
}

//partitionne le tableau t entre les indices g et d compris en utilisant la valeur 
//à la position g comme pivot 
//renvoie l'indice de la dernière case contenant une valeur inférieure au pivot (t.tab[g])

int partition(Tableau t, int g, int d){
	int i = g + 1, j = d;
	char * pivot = t.tab[g];
	char *temp;
	while(i<j){
		while(strcmp(t.tab[i], pivot) <= 0 && i<=d){i++;}//trouve un élément supérieur au pivot dans la partie gauche
		while(strcmp(t.tab[j], pivot) > 0 && j > g){j--;}//trouve un élément inférieur au pivot dans la partie droite
		if(i<j){//on échange uniquement si i < j et pas si on est arrivé à la fin du tableau
				//parce que tout est dans l'ordre 
			temp = t.tab[i];
			t.tab[i] = t.tab[j];
			t.tab[j] = temp;
			i++; j--; //on passe ldes deux éléments qu'on vient de réordonner
		}
	}
	temp = t.tab[j];//on met le pivot en position j, après j tout est strictmeent supérieur au pivot
	t.tab[j] = t.tab[g];
	t.tab[g] = temp;
	return j;
}


//tri le tableau entre indices g et d compris
void tri_rapide(Tableau t, int g, int d){
	if(d > g){
		int pos = partition(t,g,d);
  		tri_rapide(t,g,pos-1);
  		tri_rapide(t,pos+1,d);	
	}
}


//tri par comparaison en utilisant la fonction strcmp
void tri_cmp(Tableau t){
  tri_rapide(t, 0, t.n-1);
}
