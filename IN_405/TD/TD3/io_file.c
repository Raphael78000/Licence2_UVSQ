#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "io_file.h"

IO_FILE IO_open(const char *path,int access){
	IO_FILE file;

	if (access & O_CREAT){ 																												//vérifie si le fichier existe ou pas
		file.desc = open(path,access,00644);																				//autorise l'utilisateur a écrire et modifier le ficher et les groupes et autres à lire seulement
	}
	else{
		file.desc = open(path,access);																							//ouvre le fichier déjà existant
	}
	if (file.desc == -1){																													//affiche un message d'erreur dans le cas où l'ouverture de fichier n'a pas correctement été éxécutée
		printf("error openning %s : %s\n",path,strerror(errno));
		return file;
	}

	file.path = malloc((strlen(path)+1)*sizeof(char*));														//alloue la mémoire dynamiquement de la variable path de la structure IO_FILE
	strcpy(file.path,path);																												//copie le chemin d'accès au fichier de path à la variable path de la structure IO_FILE
	file.access = access;																													//accordre les autorisations accordées en paramètre à la nouvelle structure de IO_FILE

	return file;																																	//Un nouveau fichier a été crée avec son chemin d'accès et ses permissions. Données qui sont stockées en paramètre
}

int IO_close(IO_FILE file){
	int closing;

	closing = close(file.desc);																										// ferme le descripteur file.desc, de manière à ce qu'il ne référence plus aucun fichier

	if (closing == -1){
		printf("error closing %s : %s\n",file.path,strerror(errno));								//affiche un message d'erreur dans le cas où la fermeture de fichier ne sait pas correctement effectuée
		return -1;																																	//retourne -1 dans le cas où la fermeture du fichier ne s'est pas correctement effectuée
	}

	free(file.path);																															//libère la mémoire de la variable alloué dynamiquement file.path

	return 0;																																			//retourne 0 dans le cas où la fermeture de fichier s'est correctement effectuée
}

int IO_remove(const char *path){
	int supp;

	supp = unlink(path);																													//variable qui vaut -1 si la suppression du fichier a échoué

	if (supp == -1){																															//affiche un message d'erreur dans le cas où la suppression du fichier a échoué
		printf("error deletion %s : %s\n",path,strerror(errno));
		return -1;																																	//fonction retourne -1 si suppression fichier échoué
	}

	return 0;																																			//fonction retourne 0 si suppression effectué avec succès
}

int IO_char_read(IO_FILE file,char *c){
	int back;
//fonction retourne un message d'erreur si le fichier contient pas les permissions suivantes
	if (!(file.access == O_RDONLY || file.access & O_RDONLY || file.access & O_RDWR)){			//O_RDONLY vaut 0 //O_RDWR vaut 2 //O_WRONLY vaut 1
		printf("error reading %s -> file doesn't have reading permission\n",file.path);
		return -1;																																	//fonction retourne -1 dans le cas ou on dispose pas des permissions nécessaires
	}

	back = read(file.desc,c,1);																										//effectue la lecture du char passé en argument

	if (back == -1){
		printf("error reading %s : %s\n",file.path,strerror(errno));								//fonction retourne -1 dans le cas où la lecture du char a échouée
		return -1;
	}

	return 0;																																			//fonction retourne 0 si la lecture du char a été réalisée avec succès
}

int IO_char_write(IO_FILE file,const char c){
	int back;

	if (!(file.access & O_WRONLY || file.access & O_RDWR)){												//vérification si on a les permissions pour écrire
		printf("error writting %s : file doesn't have writting permission\n",file.path);
		return -1;																																	//retourne -1 dans le cas où on a pas les permissions d'écriture
	}

	back = write(file.desc,&c,1);																									//effectue l'écriture du char dans le document

	if (back == -1){																															//fonction renvoie -1 dans le cas où l'écriture a échouée
		printf("error writting %s : %s\n",file.path,strerror(errno));
	}

	return back;																																	//retourne 0 dans le cas où l'écriture s'est effectuée correctement
}

int IO_string_read(IO_FILE file,char *string,int maxSize){
	int a = 0;
	int back, a1;
//vérifie si on dispose des permissions nécessaires pour lire le fichier
	if (!(file.access == O_RDONLY || file.access & O_RDONLY || file.access & O_RDWR)){
		printf("error reading %s : the file did not open with an reading access\n",file.path);
		return -1;																																	//retourne -1 dans le cas où l'on ne dispose pas des permissions nécessaires de lecture
	}

	do{
		a1 = read(file.desc,string+a,1);																						//lit le caractère à la position
		back = back+a1;																															//back incrémenter de 0 si la lecture s'effectue correctement
		a++;
	}
	while (a1>0 && a<maxSize);

	if (a1<0){
		printf("error reading %s : %s\n",file.path,strerror(errno));
		return a1;
	}

	string[a] = '\0';																															//stocke la chaîne lue dans la variable passée en argument "string"

	return back;																																	//retourne 0 dans le cas où la lecture s'est effectuée correctement
}

int IO_string_write(IO_FILE file,const char *string,int size){
	int a = 0;																																		//Meme commentaires que la partie précèdente mais avec quelques changements
	int a1,back;

	if (!(file.access & O_WRONLY [[ file.access & O_RDWR)){
		printf("error reading %s : file did not openned with reading access\n",file.path);
		return -1;
	}

	do{
		a1 = write(file.desc,string+a,1);
		back = back+a1;
		a++;
	}
	while (a1>0 && a<size);

	if (a1<0){
		printf("error writting %s : %s\n",file.path,strerror(errno));
		return a1;
	}

	return back;
}

int IO_int_read(IO_FILE file,int *n){
	char c;
	int back = 0,a1,wrong = 0;
//fonction retourne un message d'erreur si le fichier contient pas les permissions suivantes
	if (!(file.access == O_RDONLY || file.access &  O_RDONLY || file.access & O_RDWR)){
		printf("error reading %s : file did not openned with reading access\n",file.path);
		return -1;																																	//retourne -1 dans le cas où on ne dispose pas des autorisations nécessaires
	}

	*n = 0;																																				//initialisation

	do{
		a1 = read(file.desc,&c,1);
		back = back+a1;																															//back vaut -1 dans le cas où la lecture a échouée
		if (a1 == -1){
			printf("error reading %s : %s\n",file.path,strerror(errno));
			return a1;																																//retourne -1 dans le cas où la lecture ne s'est pas effectuée correctement
		}
	}
		while (isspace(c));

		if (c == '-'){
			wrong = 1;
			a1 = read(file.desc,&c,1);
			back = back+a1;
			if (a1 == -1){
				printf("error reading %s : %s\n",file.path,strerror(errno));
				return a1;
			}
		}

		if (c<'0' || c>'9') return -1;

		do{
			(*n) = (*n)*10;
			(*n) = (*n)+c-'0';
			a1 = read(file.desc,&c,1);
			back = back+a1;
			if (a1 == -1){
				printf("error reading %s : %s\n",file.path,strerror(errno));
				return a1;
			}
		}
		while (c>='0' && c<='9');

		if (wrong){
			(*n) = (*n) * -1);
		}

		return back;
	}

int IO_int_write(IO_FILE file,const int n){
	char* amor;
	int entier = n, a = 0;
	int a1,back = 0;
//vérification des permissions d'écriture
	if (!(file.access & O_WRONLY || file.access & O_RDWR)){
		printf("error writting %s : file did not openned with write acess\n",file.path);
		return -1;
	}

	amor = malloc(12*sizeof(char*));																							//allocation dynamique de la mémoire de la variable "amor"

	if (entier<0) entier = -entier;

	do{
		amor[a] = '0'+entier%10;
		entier = entier/10;
		a++;
	}
	while (entier!=0);

	if (n<0){
		a1 = write(file.desc,'-',1);
		back = back+a1;
		if (a1<0){
			printf("error writing %s : %s\n",file.path,strerror(errno));
			return a1;
		}
	}

	while (a>0){
		a--;
		a1 = write(file.desc,amor+a,1);
		back = back+a1;

		if (a1<0){
			printf("error writing %s : %s\n",file.path,strerror(errno));
			return a1;
		}
	}

	return back;
}
