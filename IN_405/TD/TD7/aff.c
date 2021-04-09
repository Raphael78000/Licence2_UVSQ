#include "cst.h"

// The minimum amount of messages in the list
#define MIN	2
// The maximum amount of messages in the list
#define MAX 10

// Where the new message will be stocked
char new_mes[64];

/**
 * Prints the message stocked at the num-th place in mes
 * 
 * @param ( int )	        	num 		which message in mes to print
 * @param ( struct tm* ) 		time		gives the time 
 * @param ( char** )			mes 		list of messages
 * 
 * The time and date are given by the gettimeofday() and localtime() functions.
 * However, I cannot explain why they are used the way they are. If you wish 
 * to obtain more details on these functions, do not be shy to use man or Google.
 */
void aff( int num, struct tm* time, char** mes )
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	const time_t timep = tv.tv_sec;

	// Only the second message is not directly in 'mes' as it prints the time
	if ( num == 1 )
	{
		time = localtime(&timep);
		printf("%02d/%02d/%02d - %02d:%02d:%02d\n", 
				time->tm_mday, time->tm_mon+1, (time->tm_year+1900)%100, 
				time->tm_hour, time->tm_min, time->tm_sec);
	}
	else 
		printf("%s\n", mes[num] );
}

/** Initialise a list of messages
 * 
 * @param ( int* ) 		nb_mes		number of message to initialise
 * 
 * returns an initialised list of two message, with nb_mes set at MIN
 */
char** init_mes ( int* nb_mes )
{
	// The initial number of messages is MIN
	*nb_mes = MIN;
	
	// Let us alloc' the list of the message and the first MIN messages
	char** new = malloc(sizeof(char*));
	
	new[0] = malloc(sizeof(char)*64);
	new[0] = "Bonjour, ceci est un affichage informatisé";
	
	new[1] = malloc(sizeof(char));
	new[1][0] = '\0';
	
	// The newly alloc'd list is returned
	return new;
}

/** Re-initialises a list of messages
 * 
 * @param ( char** ) 	old 		list to partiallyfree
 * @param ( int* )      nb_mes		number of messages in old
 */
void reinit_mes ( char** old, int* nb_mes )
{
	// Every message after the second one must be freed
	for ( int i = MIN; i < (*nb_mes); i++ )
		free(old[i]);
	
	// Let us reset the number of messages
	(*nb_mes) = MIN;
}

/** Modifies the list of messages
 * 
 * @param ( char** ) 		old			list of messages to modify
 * @param ( int* )			nb_mes		number of messages in old
 */
void mod_mes ( char** old, int* nb_mes )
{
	// If the send's asked to re-initialise the list of messages through "init"
	if ( strcmp(new_mes, "init") == 0 )
	{
		reinit_mes(old, nb_mes);
	}
	// If the send's asked to delete the last message through "delete"
	else if ( (strcmp(new_mes, "delete") == 0) && (*nb_mes) > MIN )
	{
		// Let us free the last message and decrease the number of messages by 1
		free(old[(*nb_mes)-1]);
		(*nb_mes)--;
	}
	// Else, the sender's asked to add a new message to the list 
	else if ( (*nb_mes) < MAX )
	{
		// Let us alloc the new message, stock it in 'mes' and 
		//increase the number of messages by 1
		old[(*nb_mes)] = malloc(sizeof(char)*strlen(new_mes));
		strcpy(old[(*nb_mes)], new_mes);
		(*nb_mes)++;
	}
	
	// The new message has been treated so the first character of 
	// 'new_mes' is set to '\0'
	new_mes[0] = '\0';
}

/** Function called when receiving the SUGUSR2 signal.
 * 	It copies the message written in the pipe in new_mes
 * 
 * Let x be a integer between 0 and 9 and let a be a character
 * if  a = 'x' 		then  a = x + 48
 */
void receive()
{
	// First, let us read the length of the message
	char n[2];
	read(fd, n, 2);
	
	// A local atoi() function 
	int l = (n[0]-48)*10 + (n[1]-48);
	char s[l];
	
	// O is returned of the end of the file has been reached
	if ( read(fd, s, l) )
	{
		// Let us copy the first 'l' characters of 's' in 'new_mes'
		strncpy(new_mes, s, l);
	}
	
	// This printf notifies the user of the new message
	printf("New message added : %s\n", new_mes);
	
	// Eveyrthing after the new message is set to '\0'
	for ( l; l <64; l++ )
		new_mes[l] = '\0';
}

/**	Frees a list of messages
 * 
 * @param ( char** )	old			list of messages to free
 * @param ( int ) 		nb_mes		number of messages to free in 'old'
 * 
 * The reinit_mes() function is called to partially free the 
 * list of messages. The rest is freed in this function.
 */
void free_mes ( char** old, int nb_mes )
{
	if ( nb_mes > MIN ) reinit_mes(old, &nb_mes);
	
	free(old[0]);
	free(old[1]);
	free(old);
}

void main()
{	
	// Let us create the tube that will be used by aff and new
	if ( mkfifo(path, 0666 ) == -1 )
	{ 
		printf("error mkfifo\n");
		return;
	}
	
	// Let us open the tube so it can be written in
	fd = open(path, O_WRONLY);
	if ( fd == -1 )
	{
		printf("error fd aff wr\n");
		return;
	}
	
	// Let us write the PID of the process in the tube so the 
	// sender can have a process to send the messages to 
	pid_t p = getpid();
	write(fd, &p, sizeof(pid_t));
	close(fd);
	
	// Let us open the tube so it can be read
	fd = open(path, O_RDONLY);
	if ( fd == -1 )
	{
		printf("error fd aff rd\n");
		return;
	}
	
	// 'time' is alloc here so it can be used later in aff()
	struct tm* time = malloc(sizeof(struct tm));
	int nb_mes = 0;
	char** mes = init_mes(&nb_mes);
	new_mes[0] = '\0';
	
	// Copy and paste from the fourth exercice from TD6
	// except for the function to call when receiving a signal
	struct sigaction act;
	act.sa_handler = receive;
	act.sa_flags = SA_ONSTACK;
	sigaction(SIGUSR2, &act, NULL);
	
	// The main loop that is infinite	
	for ( unsigned int i = 0; 1; i++ )
	{
		// Let us print the message depending on 'i%nb_mes'
		aff((i%nb_mes), time, mes);
		
		sleep(2);
		
		// If 'new_mes' has a new_message, it must be treated 
		if ( new_mes[0] != '\0' ) 
			mod_mes(mes, &nb_mes);
			
	}
	
	// Let us free everything alloc'd
	free(time);
	free_mes(mes, nb_mes);
}
