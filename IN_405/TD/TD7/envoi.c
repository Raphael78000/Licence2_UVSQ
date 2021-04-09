#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define TAILLE_MAX 1024
#define CHEMIN "/home/user/Bureau/UVSQ/S4/IN405/TD7 -- Communication/tube-test"

int main(int argc,char **argv){

	if(argc < 3){
		printf("Invalid number of arguments, expected at least 2 (mode, pid, (sentence?))\n");
		return 1;
	}
	
	else if(argc == 3 && atoi(argv[1])){
		printf("mode expects a sentence to add\n");
		return 1;
	}
	
	else if(!atoi(argv[1])){
		kill(atoi(argv[2]),SIGUSR2);
	}
	
	else if(atoi(argv[1])){
		
		//permet d'envoyer grace aux arguments une phrase complète
		int fin_phrase = 0; int mot = 3;
		char mes[TAILLE_MAX]; 
		strcpy(mes,"\0");
		while(mot < argc && fin_phrase < TAILLE_MAX){
			if(mes == "\0") strcpy(mes,argv[mot]);
			else strcat(mes, argv[mot]);
			strcat(mes," ");
			fin_phrase += 1 + strlen(argv[mot]);
			mot++;
		}
		mes[fin_phrase] = '\0';

		int fd;
		mkfifo(CHEMIN,0666);
		kill(atoi(argv[2]),SIGUSR1);
		fd = open(CHEMIN,O_WRONLY);
		write(fd,mes,strlen(mes));
		close(fd);
	}
		
	return 0;
}
