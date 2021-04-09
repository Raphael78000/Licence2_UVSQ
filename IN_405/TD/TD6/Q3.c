#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
* SIGINT = le signal envoyé à un processus afin de provoquer son interruption
* SIGCONT = Demande de reprise du processus
*	SIGSTOP = Demande de suspension imbloquable
*/

void pere(const pid_t a){
	sleep(3);
	kill(a,SIGSTOP);																															//send a signal to a process
	sleep(3);
	kill(a,SIGCONT);
}

void fils(){
	int i = 1;

	while (i < 6){
		sleep(1);
		printf("Attente à %dsec.\n",i);
		++i;
	}
	exit(0);
}

int main (int argc,char ** argv){
	pid_t a;
	if (a = fork()) pere(a);
	else fils();

	wait(NULL);

	return 0;
}
