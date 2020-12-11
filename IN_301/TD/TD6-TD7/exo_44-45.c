#include <stdio.h>


void affbitschar(char *label, unsigned char c) {
	// Exemple
	// c = 0100 1110
	// quand i vaut 6, 1<<6 vaut 0100 0000
	// c        = 0100 1110
	// 1<<6     = 0100 0000
	// c & 1<<6 = 0100 0000
	printf("%s = %03u %02x  ",label,c,c);
	int i;
	for (i=7 ; i>=0 ; i--) {
		if (c & 1<<i) printf("1"); else printf("0");
		if (i==4) printf(" ");
	}
	printf("\n");
}

void bitabit () {
	unsigned char a,b,c;
	a = 13;		affbitschar("a    ",a);
	b = 3;		affbitschar("b    ",b);
	c = a & b;	affbitschar("a & b",c); // ET bit à bit
	c = a | b;	affbitschar("a | b",c); // OU (INCLUSIF) bit à bit
	c = a ^ b;	affbitschar("a ^ b",c); // OU EXCLUSIF (XOR) bit à bit
	c = ~a;		affbitschar("~a   ",c); // NON bit à bit
}
