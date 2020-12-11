#include <stdio.h>
#include "exo_45.h"

void affbitschar(unsigned char){
  unsigned char a = 128;

  printf("\n");
  for (int i = sizeof(unsigned char)*8; i > 0 ; i--){
    printf("%d ",(c&a)>>(i-1));
    a= a>>1;
  }
  printf("\n");
}
