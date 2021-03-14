#include "internals.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>



void print_file(const struct file* fichier){
	const struct file* navig;
	
	navig = fichier;
	
	if (!navig){
		printf("error %s\n",strerror(errno));
		return;
	}
	
	while (navig->next != NULL){
	printf("navig->name = %s\n",navig->name);
	navig = navig->next;
	}
}

int main(int argc, char **argv){
  struct file** origin;
  
  //origin = malloc(sizeof(struct file*));
  
  /*if (argc != 3){
    printf("Bad usage: %s src dest\n"
           "   - src : source directory\n"
           "   - dest: phantom directory\n", argv[0]);
    return EXIT_FAILURE;
  }*/

 browse_directory(argv[1],origin);
 
 //create_regular(argv[2],*origin);

print_file(*origin);
  
  


    return 0;
}
