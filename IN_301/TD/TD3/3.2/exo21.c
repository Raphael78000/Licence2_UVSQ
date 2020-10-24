#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void majuscule(char* s){
	int t;
	
	for (int a=0;a<strlen(s);a++){
		t=s[a];
		if (t>=97 && t<=122){
			s[a]=t-32;
		}
		printf("%c\n",s[a]);
	}
}
void minuscule(char* s){
	int t;
	
	for (int a=0;a<strlen(s);a++){
		t=s[a];
		if (t>=65 && t<=90){
			s[a]=t+32;
		}
		printf("%c\n",s[a]);
	}
}
char* duplique(char* s){
	char* copie;
	
	if (s!=NULL){
		copie=malloc((strlen(s) + 1) * sizeof(char*));//créer un tableau de la taille de la chaîne
		strcpy(copie, s);//copie la chaîne de s à copie
	}
	return copie;//l'utilisation de la fonxtion libère la mémoire automatiquement après utilisation de la fonction
}
char *cherche(char *s, char c) {
	char* occ;
	for (int a=0;a<strlen(s);a++){
		if (s[a]==c){
			occ=&s[a];
			return occ;
		}
	}
	return NULL;
}
char *concatene(char *s1, char *s2){
	char* c;

	c=malloc(sizeof(char*)*(strlen(s1)+strlen(s2)+1));
	c=strcat(s1,s2);
	return c;
 }
int difference(char *s1, char *s2){
	int diff;
	
	diff=s1[0]-s2[0];
	return diff;
}
char *souschaine(char *s1, char *s2){
	int i,j;
	int l=0;
	char* ss;
	
	i=strlen(s1);
	j=strlen(s2);
	for (int k=0;k<=i;k++){
		if (s1[k]==s2[l]){
			l++;
		}
		if (l==j){
			ss=&s1[(k-l)+1];
			return ss;
		}
	}
}
int main(int argc,char** argv){

	return 0;
}
