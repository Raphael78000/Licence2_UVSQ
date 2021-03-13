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

int main(int argc, char **argv){
  struct file* origin;
  
  origin = malloc(sizeof(struct file));
  printf("adresse mémoire origin:   %p\n",origin);


  /*if (argc != 3){
    printf("Bad usage: %s src dest\n"
           "   - src : source directory\n"
           "   - dest: phantom directory\n", argv[0]);
    return EXIT_FAILURE;
  }*/
 browse_directory(argv[1],&origin);

    return 0;
}
