#include <stdio.h>
#include <stdlib.h>
#include "exo_42.h"

void decalage() {
	unsigned char x,y,z;
	x = -1;
	printf(" %03u %02x\n",x,x);
	y = x<<1;
	printf(" %03u %02x\n",y,y);
	z = y>>4;
	printf(" %03u %02x\n",z,z);
	x = 1;
	printf(" %03u %02x\n",x,x);
	x = x<<1;
	printf(" %03u %02x\n",x,x);
	x = x<<5;
	printf(" %03u %02x\n",x,x);
	x = x>>3;
	printf(" %03u %02x\n",x,x);
	x = x<<4;
	printf(" %03u %02x\n",x,x);
	x = x<<1;
	printf(" %03u %02x\n",x,x);
}
