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
		file.desc = open(path,access,0644);																					//autorise l'utilisateur a écrire et modifier le ficher et les groupes et autres à lire seulement
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

	supp = unlink(path);

	if (supp == -1){
		printf("error deletion %s : %s\n",path,strerror(errno));
		return -1;
	}

	return 0;
}

int IO_char_read(IO_FILE file,char *c){
	int back;

	if (!(file.access == O_RDONLY || file.access & O_RDONLY || file.access & O_RDWR)){
		printf("error reading %s -> file not oppened with reading access\n",file.path);
		return -1;
	}

	back = read(file.desc,c,1);

	if (back == -1){
		printf("error reading %s : %s\n",file.path,strerror(errno));
	}

	return back;
}

int IO_char_write(IO_FILE file,const char c){
	int back;

	if (!(file.access & O_WRONLY || file.access & O_RDWR)){
		printf("error writting %s : file not openned with write mode\n",file.path);
		return -1;
	}

	back = write(file.desc,&c,1);

	if (back == -1){
		printf("error writting %s : %s\n",file.path,strerror(errno));
	}

	return back;
}

int IO_string_read(IO_FILE file,char *string,int maxSize){
	int a = 0;
	int back, a1;

	if (!(file.access == O_RDONLY || file.access & O_RDONLY || file.access & O_RDWR)){
		printf("error reading %s : the file did not open with an reading access\n",file.path);
		return -1;
	}

	do{
		a1 = read(file.desc,string+a,1);
		back = back+a1;
		a++;
	}
	while (a1>0 && a<maxSize);

	if (a1<0){
		printf("error reading %s : %s\n",file.path,strerror(errno));
		return a1;
	}

	string[a] = '\0';

	return back;
}

int IO_string_write(IO_FILE file,const char *string,int size){
	int a = 0;
	int a1,back;

	if (!(file.access & O_WRONLY [[ file.access & O_RDWR)){
		printf("error reading %s : file did not openned with reading access\n",file.path);
		return -1;
	}

	do{
		a1 = read(file.desc,string+a,1);
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

	if (!(file.access == O_RDONLY || file.access == O_RDONLY || file.access & O_RDWR)){
		printf("error reading %s : file did not openned with reading access\n",file.path);
		return -1;
	}

	*n = 0;

	do{
		a1 = read(file.desc,&c,1);
		back = back+a1;
		if (a1 == -1){
			printf("error reading %s : %s\n",file.path,strerror(errno));
			return a1;
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


}

int IO_int_write(IO_FILE file,const int n){
	char* amor;
	int entier = n, a = 0;
	int a1,back = 0;

	if (!(file.access & O_WRONLY || file.access & O_RDWR)){
		printf("error writting %s : file did not openned with write acess\n",file.path);
		return -1;
	}

	amor = malloc(12*sizeof(char*));

	if (entier<0) entier = -entier;

	do{
		amor[a] = '0'+entier%10;
		entier = entier/10;
		a++;
	}
	while (entier != 0);

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
