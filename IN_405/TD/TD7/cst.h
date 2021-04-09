
// Here are all the libraries used in aff and new 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

// path to the tube used in in both aff and new
#define path "./fifo"

// File descriptor as global variable so every 
// function can have access to the tube
int fd =  0;
