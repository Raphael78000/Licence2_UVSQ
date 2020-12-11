#include <stdio.h>
#include <stdlib.h>
#include "exo_46-47.h"


void affbitsfloat (float x) {
	unsigned int *p = (unsigned int *)&x; // cast
	unsigned int n = *p;
	printf("%36.30f = %08x = ",x,n);
	int pos;
	for (pos = 1 ; pos<=32 ; pos++) {
		unsigned int a = (n>>(32-pos)) & 1;
		if (a) printf("1"); else printf(".");
		if (pos == 1) printf("|");
		if (pos == 9) printf("|");
		if (pos%4 == 0) printf("  ");
	}
	printf("\n");
}

void precision() {
	//~ affbitsfloat(0.25);
	//~ affbitsfloat(0.5);
	//~ affbitsfloat(0.0);
	//~ affbitsfloat(1.0);
	//~ affbitsfloat(2.0);
	//~ affbitsfloat(1.9999999);
	//~ affbitsfloat(1.99999999);
	//~ affbitsfloat(0.00000000001234);
	
	// affbitsfloat(2.0);
	// affbitsfloat(2.25);
	// affbitsfloat(2.50);
	// affbitsfloat(2.75);
	// affbitsfloat(3.999999);
	// affbitsfloat(1.0/3.0);
	float a,b,c,d;
	a = 1e-8;     // 0,00000001
	b = a + 1.0;  // 1,00000001
	c = b - 1.0;  // 0,00000001
	d = (a + 1.0) - 1.0; // 0,00000001
	affbitsfloat(a);
	affbitsfloat(b);
	affbitsfloat(c);
	affbitsfloat(d);
	
	if (c==d) printf("ok\n"); else printf("pb\n");

}
/*
234,56
=
2*10² + 3*10¹ + 4*10⁰ + 5*10⁻¹ + 6*10⁻²

101,1101
=
1*2² + 0*2¹ + 1*2⁰ + 1*2⁻¹ + 1*2⁻² + 0*2⁻³ + 1*2⁻⁴
=
2² + 2⁰ + 2⁻¹ + 2⁻² + 2⁻⁴
=
4  + 1  + 1/2 + 1/4 + 1/16
=5,8125

0,1   = 1/2
0,01  = 1/4
0,011 = 1/4 + 1/8 = 0,375
0,0101 = 1/4 + 1/16 = 0,3125
*/

/*
1.0/3.0 =
0,010  1010  1010  1010  1010  1011
   2   4 6   8 10 12 14 16 18 20 22 23

= 2⁻² + 2⁻⁴ + 2⁻⁶ + ... + 2⁻²³

   1     1     1           1
= --- + --- + --- + ... + ----
   2²    2⁴    2⁶          2²³

  2²¹ + 2¹⁹ + 2¹⁷ + 2¹⁵ + 2¹³ + 2¹¹ + 2⁹ + 2⁷ +2⁵ + 2³ + 2 + 1
= ------------------------------------------------------------
                              2²³
2²³ = 8388608

2²¹ = 2097152
2¹⁹ =  524288
2¹⁷ =  131072
2¹⁵ =   32768
2¹³ =    8192
2¹¹ =    2048
2⁹  =     512
2⁷  =     128
2⁵  =      32
2³  =       8
2   =       2
1   =       1
TOT = 2796203
2796203 / 8388608 = 0,333333373069763


2796202 / 8388608 = 0,333333253860474

                    2796202   1   2796203
0,333333253860474 = ------- < - < ------- = 0,333333373069763
                    8388608   3   8388608

*/
