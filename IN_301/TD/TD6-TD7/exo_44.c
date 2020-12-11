#include <stdio.h>
#include "exo_44.h"

void bitabit(){
  unsigned char a,b,c;

  a = 13;
  b = 3;

  c = a&b;
  printf("%03u %02x\n",c,c);

  c = a|b;
  printf("%03u %02x\n",c,c);

  c = a^b;
  printf("%03u %02x\n",c,c);

  c = ~a;
  printf("%03u %02x\n",c,c);
}
