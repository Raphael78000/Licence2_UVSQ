#include <stdio.h>

#define N 100
#define carre(x) ((x)*(x))
#define deuxfois(x) ((x)+(x))
#define plus(x,y) ((x)+(y))
#define max(x,y) (((x)>(y)) ? (x) : (y))
#define min(x,y) (((x)<(y)) ? (x) : (y))
//#define max3(x,y,z) ((max(x,y)>(z)) ? max(x,y) : (z))
//#define max3(x,y,z) (((x>y))?   (((x)>(z)) ? (x) : (z)) : ((y)>(z)) ? (y) : (z))
#define max3(x,y,z) max(max(x,y),(z))
#define max4(x,y,z,t) max(max3(x,y,z),(t)
#define swap(x,y) ((x)^=(y) , (y)^=(x ), (x)^=(y))
#define affint(x) printf(#x" = %d\n",x)

//     x           y
// 0000 1100   0000 0111
// x = x^y
// 0000 1011   0000 0111
// y = y^x
// 0000 1011   0000 1100
// x = x^y
// 0000 0111   0000 1100 

// a est le ième bit de x (a vaut 0 ou 1)
// b est le ième bit de x (b vaut 0 ou 1)
//  ième bit de x                     ième bit de y
//        a                                  b
//     a XOR b                               b
//     a XOR b                         b XOR (a XOR b)
// (a XOR b) XOR ((a XOR b) XOR b)     b XOR (a XOR b)
// (a XOR b) XOR       a                    a
//  b XOR a XOR a                           a
//        b                                 a


// Propriété 1 : XOR est commutatif et associatif
// Propriété 2 : quelque soit x : x XOR x = 0
// Propriété 3 : quelque soit x : x XOR 0 = x
// Propriété 4 : a XOR b XOR b = a

// a b (a XOR b)  ((a XOR b) XOR b)
// 0 0     0            0
// 0 1     1            0
// 1 0     1            1
// 1 1     0            1


// Opérateurs unaires
// -x, +x, ++x, x++, --x, x--, &x, *x, ~x, !x, ()

// Opérateurs binaires
// x+y, x-y, x*y, x/y, x%y, x=y,
// x!=y, x==y, x>y, x>=, x<y, x<=y
// x+=y, x-=y, x*=y, x/=y,, x%=y,
// x<<=y, x>>=y, x&=y, x^=y, x|=y,
// x&&y, x||y, x&y, x|y, x^y
// x<<y, x>>y
// x.y, x[y], p->y

// Opérateurs ternaire
// x?y:z


void macros() {
	int a = N;
	printf("a = %d\n",a);
	float x;
	x = carre(2.3);
	printf("x = %f\n",x);
	a = carre(7);
	printf("a = %d\n",a);
	a = 6*deuxfois(5);
	printf("a = %d\n",a);
	a = plus(5,7);
	printf("a = %d\n",a);
	a = max(5,7);
	printf("a = %d\n",a);
	a = min(5,7);
	printf("a = %d\n",a);
	a = max3(5,7,6);
	printf("a = %d\n",a);
	int b;
	a = 12;
	b = 7;
	printf("%d %d\n",a,b);
	swap(a,b);
	printf("%d %d\n",a,b);
	affint(a);

}
