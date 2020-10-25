#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int test_float(char* chaine){
	int i = 0;
	if(chaine[0] == '-'){
		i++;
		}

	for(;i<strlen(chaine);i++){
		
		if(chaine[i]=='.'){
			i++; 
			break;
			}
		if(isdigit(chaine[i])==0){
			printf("%s n'est pas un nombre\n",chaine);
			return 0;
		}
	}

	for(;i< strlen(chaine); i++){
		if(isdigit(chaine[i])==0){
			return 0;
	}
	return 1;
	}
}

int main(int argc, char** argv){

	double somme = 0;
	printf("argc = %d\n", argc);

	for(int i = 1; i<argc; i++){
		if(test_float(argv[i])){
			somme += atof(argv[i]);
			}
		}
		printf("%f\n",somme);
		
		return 0;
	}
