#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void fils(int a){
	sleep(a);																																			//delay for a specified amount of time
	printf("%d [%d]\n",getpid(),a);

	exit(0);
}

int main(int argc,char** argv){
	pid_t a;

	srand(time(NULL));

	for (int i = 0;i < 10;++i){
		// Génération dans le processus pere pour sortir les nombres de la
		// même graine
		int r = 1 + (rand() % 10);
		if (!fork()){																																//on entre dans la boucle du processus fil s'il existe
			fils(r);
		}
	}

	for (int i = 0;i < 10;++i){																										//dans la boucle du processus père 
		a = wait(NULL);
		printf("%d est fini\n",a);
	}

	return 0;
}
