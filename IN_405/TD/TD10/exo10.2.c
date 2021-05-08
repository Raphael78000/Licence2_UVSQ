#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void* handler ( void* arg )
{
	pthread_barrier_t* barrier = (pthread_barrier_t*) arg;
	printf("Attendre....\n");
	pthread_barrier_wait(barrier);
	printf(" Fini | ");
	return NULL;
}

void main( int argc, char** argv )
{
	int nbThreads = atoi(argv[1]);
	int nbLoop = atoi(argv[2]);
	pthread_t* thread;
	pthread_barrier_t* barrier;
	
	thread = malloc(sizeof(pthread_t)*nbThreads);
	barrier = malloc(sizeof(pthread_barrier_t));
	
	for ( int j = 0; j < nbLoop; j++ )
	{
		pthread_barrier_init(barrier, NULL, nbThreads);
		
		for ( int i = 0; i < nbThreads; i++ )
		{
			if ( i == nbThreads-1 ) sleep(j+1);
			pthread_create(&(thread[i]), NULL, handler, (void*) barrier);
		}
			
		for ( int i = 0; i < nbThreads; i++ )
			pthread_join(thread[i], NULL);
			
		printf("\nAttempt n°%d done !\n\n", j+1);
			
		pthread_barrier_destroy(barrier);
	}
	
	free(thread);
	free(barrier);
}
