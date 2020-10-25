#include <stdio.h>
#include <stdlib.h>

int longueur(char* chaine){
	int i;
	for(i=0;chaine[i]!='\0'; i++){}
	return i;
}
void majuscule(char* s){
	int t;
	
	for (int a=0;a<longueur(s);a++){
		t=s[a];
		if (t>=97 && t<=122){
			s[a]=t-32;
		}
		printf("%c\n",s[a]);
	}
}
void minuscule(char* s){
	int t;
	
	for (int a=0;a<longueur(s);a++){
		t=s[a];
		if (t>=65 && t<=90){
			s[a]=t+32;
		}
		printf("%c\n",s[a]);
	}
}
char* duplique(char* s){
	char* copie;
	int a;
	
	if (s!=NULL){
		copie=malloc((longueur(s)+1) * sizeof(char*));//créer un tableau de la taille de la chaîne
		for (a=0;s[a]!='\0';a++){//copie la chaîne de s à copie
			copie[a]=s[a];
		}
		copie[a]='\0';
	}
	return copie;//l'utilisation de la fonxtion libère la mémoire automatiquement après utilisation de la fonction
}
char *cherche(char *s, char c) {
	char* occ;
	for (int a=0;a<longueur(s);a++){
		if (s[a]==c){
			occ=&s[a];
			return occ;
		}
	}
	return NULL;
}
char *concatene(char *s1, char *s2){
	char* c;
	int a,b;

	c=malloc(sizeof(char*)*(longueur(s1)+longueur(s2)));
	for (a=0;s1[a]!='\0';a++){
		c[a]=s1[a];
		}
	for (b=0;s2[b]!='\0';b++,a++){
		c[a]=s2[b];
		}
		c[a]='\0';
		
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
	
	i=longueur(s1);
	j=longueur(s2);
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
char* c;
c=concatene(argv[1],argv[2]);
printf("%s\n",c);
	return 0;
}
