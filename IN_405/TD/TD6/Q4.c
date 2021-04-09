#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 1;
/*
* SIGUSR = Signal utilisateur
*/
void pere(const pid_t a){
	sleep(3);
	kill(a,SIGUSR1);
	sleep(2);
	kill(a,SIGUSR1);
	sleep(3);
	kill(a,SIGUSR1);
}

void handler(int a){
	printf("debug: %d\n",counter);
}

void fils(){
	struct sigaction act;																													//examiner et modifier l'action associée à un signal

	act.sa_handler = handler;
	// Empêcher l'execution du comportement par défaut de SIGUSR1 -> SIGTERM
	act.sa_flags = SA_ONSTACK;

	sigaction(SIGUSR1,&act,NULL);																									//examine and change a signal action

	while (counter < 12){
		sleep(1);
		printf("Attente à %dsec.\n",counter);
		++counter;
	}

	exit(0);
}

int main(int argc,char ** argv){
	pid_t a;
	if (a = fork()) pere(a);
	else fils();

	wait(NULL);

	return 0;
}
