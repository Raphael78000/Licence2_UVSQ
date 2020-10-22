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
		return 1+recursive_longueur(chaine+1);//ajoute 1 et renvoie un appel a la fonction en diminuant la chaîne de caractère d'une lettre en partant de la gauche 
	}
}
int compare(char * chaine1, char * chaine2){
	int i;
	for(i=0;i<strlen(chaine1) && strlen(chaine2) && chaine1[i]==chaine2[i];i++){}
	if (chaine1[i]==chaine2[i]){
		//printf("les deux chaînes ont la même longueur\n");
		return 0;
	}
	if (chaine1[i]<chaine2[i]){
		//printf("%s est plus petite que %s\n",chaine1,chaine2);
		return -1;
		}
		else
		{
			//printf("%s est plus grande que %s\n",chaine1,chaine2);
			return 1;
			}
}

int main( int argc, char** argv){
	/*for (int i=1;i<argc;i++){
		printf("argv[%d]=%d\n",i,longueur(argv[i]));
		recursive_longueur(argv[i]);
		printf("argv[%d]=%d\n",i,recursive_longueur(argv[i]));
	}*/

return 0;   
}

