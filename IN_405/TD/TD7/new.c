#include "cst.h"

// The process identification of the receiver
pid_t pid;

/** Writes a message in the tube, then
 * 	sends a signal to the receiver.
 * 	Kills the receiver and itself if the message is "quit".
 */
void send()
{
	char s[64];
	// Waiting for an input from the user 
	// WARNING : the message CANNOT have spaces between its words
	scanf("%s", &s);
	int l = strlen(s);
	
	if ( l > 64 ) // Messages longer than 64 bits are not accepted
	{
		printf("error message too long\n");
		return;
	}
	
	if ( strcmp("quit", s) == 0 ) // If the user desires to end the processes
	{
		// The tube is no longer needed
		close(fd);
		// fd is set to 0 to end the while loop in main()
		fd = 0;
		// The tube is no longer needed as well so let us delete it
		unlink(path);
		
		// SIGINT terminates the process of the receiver 
		kill( pid, SIGINT);
		return;
	}
	else 
	{
		// n is a string of two characters describing the length of the message
		char n[2];
		n[1] = l%10 + 48;
		n[0] = l/10 + 48;
		
		// if write() returns a value lesser than the number of characters
		// written, then there has been an error while writing
		
		// The length of the message is written first
		// The message itself is written second
		if ( (2 > write(fd, n, 2)) || (l > write(fd, s, l)) )
		{
			printf("error write new\n");
			return;
		}
		
		// The '\0' character is written last to signify the end of a string
		write(fd, '\0', 1);
		
		// Now that the message is ready to be read, the receiver is notified 
		kill( pid, SIGUSR2);
		printf("\nMessage sent : %s\n", s);
	}
}

void main()
{
	// Let us open the tube so it can be read
	fd =  open(path, O_RDONLY);
	if ( fd == -1 )
	{
		printf("error fd new rd\n");
		return;
	}
	
	// The PID of the receiver should be in the tube 
	// It shall be written in pid 
	read(fd, &pid, sizeof(pid_t));
	close(fd);
	
	// Let us open the tube so it can be written in
	fd =  open(path, O_WRONLY);
	if ( fd == -1 )
	{
		printf("error fd new wr\n");
		return;
	}
	
	// As long as file descriptor isn't set to 0
	while ( fd )
	{
		// Keep sending messages to the receiver
		send();
	}
}
