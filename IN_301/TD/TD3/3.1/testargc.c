#include <stdio.h>
#include <string.h>

int main( int argc, char** argv){

int i;
printf("argc = %d\n", argc);
for(i=0 ; i<argc ; i++)
printf("%s %d\n", argv[i],strlen(argv[i]));

return 0;
}
