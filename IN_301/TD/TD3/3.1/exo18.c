#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longueur(char* chaine){
	int i;
	for(i=0;chaine[i]!='\0'; i++){}
	return i;
}
int recursive_longueur(char* chaine){
	if (chaine[0]=='\0'){
		return 0;
	}
	else{
		return 1+recursive_longueur(chaine+1);
		//ajoute 1 et renvoie un appel a la fonction en diminuant la chaîne de caractère d'une lettre en partant de la gauche 
		//déplace le début de la chaîne de une lettre
	}
}
int compare(char* chaine1, char* chaine2){
	int i;
	for(i=0;i<strlen(chaine1) && strlen(chaine2) && chaine1[i]==chaine2[i];i++){}
	if (chaine1[i]==chaine2[i]){
		printf("les deux chaînes ont la même longueur par méthode itérative\n");
		return 0;
	}
	if (chaine1[i]<chaine2[i]){
		printf("%s est plus petite que %s par méthode itérative\n",chaine1,chaine2);
		return -1;
		}
		else
		{
			printf("%s est plus grande que %s par méthode itérative\n",chaine1,chaine2);
			return 1;
			}
}
int compar_recursive(char* chaine1,char* chaine2){
	if (chaine1[0]==chaine2[0] && chaine1[0]=='\0'){
		return 0;
	}
	if(chaine1[0]==chaine2[0]){
		return compar_recursive(chaine1+1,chaine2+1);
}
	if(chaine1[0]<chaine2[0]){
		return -1;
	}
	else{
		return 1;
	}
}

int main( int argc, char** argv){

	printf("argv[1]=%d par méthode itérative\n",longueur(argv[1]));
	printf("argv[1]=%d par méthode récursive\n",recursive_longueur(argv[1]));
	printf("argv[2]=%d par méthode itérative\n",longueur(argv[2]));
	printf("argv[2]=%d par méthode récursive\n",recursive_longueur(argv[2]));
	switch (compare(argv[1],argv[2])){
		case -1:
		printf("%s est plus petite que %s par méthode récursive\n",argv[1],argv[2]);
		break;
		case 0:
		printf("les deux chaînes ont la même longueur par méthode récurisve\n");
		break;
		case 1:
		printf("%s est plus grande que %s par méthode récursive\n",argv[1],argv[2]);
		break;
	}

return 0;   
}

