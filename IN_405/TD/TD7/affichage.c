#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>

#define NB_MES_MAX 20
#define TAILLE_MAX 1024
#define CHEMIN "/home/user/Bureau/ -- Communication/tube-test"

//variables globales
char mes[NB_MES_MAX][TAILLE_MAX];
char str[TAILLE_MAX];
int nb_mes;
int fd; int rc;

//q3_affichage
void affiche_temps(){
	struct tm* time;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	const time_t timep = tv.tv_sec;
	time = localtime(&timep);
	printf("%02d/%02d/%02d - %02d:%02d:%02d\n", time->tm_mday, time->tm_mon+1,
	      (time->tm_year+1900)%100, time->tm_hour, time->tm_min, time->tm_sec);
}

void init_mes(){
	strcpy(mes[0],"Bonjour, ceci est un message informatisé");
	strcpy(mes[1],"timeofday");
	nb_mes = 2;
}


void q3_affichage(){
	int i=0;
	while(1){
		sleep(2);
		if(!strcmp(mes[i],"timeofday")){
			affiche_temps();
		}
		else printf("%s\n",mes[i]);
		i=(i+1)%nb_mes;
	}
}

//q4_reception
void add_message(){
	if(nb_mes == NB_MES_MAX){
		printf("no space available\n");
		return;
	}

	fd = open(CHEMIN,O_RDONLY);
	rc = read(fd,str,TAILLE_MAX);
	str[rc] = '\0';
	strcpy(mes[nb_mes],str);
	nb_mes++;

	close(fd);
	unlink(CHEMIN);
}

void reset_message(){
	while(nb_mes > 2){
		strcpy(mes[nb_mes],"\0");
		nb_mes--;
	}
}

int main(){
	printf("here's my pid : %d\n",getpid());
	init_mes();
	int nb_mes = 2;

	struct sigaction sig;
	sig.sa_flags = SA_ONSTACK;

	sig.sa_handler = add_message;
	sigaction(SIGUSR1,&sig,NULL);

	sig.sa_handler = reset_message;
	sigaction(SIGUSR2,&sig,NULL);

	q3_affichage();
	return 0;
}
