#include <stdio.h>
#include <stdlib.h>
#include "exo_42.h"

void decalage() {
	unsigned char x,y,z;
	x = 33; 	// 0010 0001
	printf(" %03u %02x\n",x,x);
	x = x<<1; 	// 0100 0010
	printf(" %03u %02x\n",x,x);
	x = x<<5;	// 0100 0000
	printf(" %03u %02x\n",x,x);
	x = x>>3;	// 0000 1000
	printf(" %03u %02x\n",x,x);
	x = x<<4;	// 1000 0000
	printf(" %03u %02x\n",x,x);
	x = x<<1;	// 0000 0000

	printf("##\n");

	x = -1;		// 1111 1111
	printf(" %03u %02x\n",x,x);
	y = x<<1;	// 1111 1110
	printf(" %03u %02x\n",y,y);
	z = y>>4;	// 0000 1111
	printf(" %03u %02x\n",z,z);
}
