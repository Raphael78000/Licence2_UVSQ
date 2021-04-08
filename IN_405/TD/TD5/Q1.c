#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void question1(){
	pid_t a = fork(); 																														//fork - create child process

	printf("Hello World!\n");
	if (a) wait(NULL); 																														//wait - wait for process to change state
	else exit(0);
}

void question2(){
	pid_t a = fork();																															//fork - create child process

	if (a){																																				//partie du processus père
		printf("Mon PID est %d et celui de mon fils est %d !\n",getpid(),a);
		wait(NULL);
	}
	else{																																					//partie du processus fils
		printf("Mon PID est %d et celui de mon pere est %d !\n",getpid(),getppid());
		exit (0);
	}
}

void question3(){
	srand(time(NULL));
	pid_t a = fork();

	if (a){																																				//partie du processus père
		int status;
		wait(&status);

		printf("Valeur choisie par mon fils: %d.\n",WEXITSTATUS(status));						//retourne le code de retour du processus fils
	}
	else{																																					//partie du processus fils
		int valeur = 1 + (rand() % 50);
		printf("Valeur choisie aleatoirement: %d.\n",valeur);
		exit(valeur);
	}
}

int main(int argc,char ** argv){
	question1();
	question2();
	question3();

	return 0;
}
