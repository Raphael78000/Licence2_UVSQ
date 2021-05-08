#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void* handler ( void* arg )
{
	return NULL;
}

void main()
{
	srand(getpid());
	int nbThreads = rand()%100 + 1;
	char** mes;
	pthread_t* thread;
	pthread_cond_t* cond;
	pthread_mutex_t* mutex;
	
	thread = malloc(sizeof(pthread_t)*nbThreads);
	cond = malloc(sizeof(pthread_cond_t));
	mutex = malloc(sizeof(pthread_mutex_t));

	mes = malloc(sizeof(char*)*nbThreads);
	for ( int i = 0; i < nbThreads; i++ )
	{
		mes[i] = malloc(sizeof(char)*100);
		mes[i][0] = '\0';
	}
	
	pthread_cond_init(cond, NULL);
	
	for ( int i = 0; i < nbThreads; i++ )
		pthread_create(&(thread[i]), NULL, handler, NULL);
			
	for ( int i = 0; i < nbThreads; i++ )
		pthread_join(thread[i], NULL);
	
	
	pthread_cond_destroy(cond);
		
	free(thread);
	free(cond);
	free(mutex);
	for ( int i = 0; i < nbThreads; i++ )
		free(mes[i]);
	free(mes);
}
