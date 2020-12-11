#include <stdio.h>

// 2¹⁰ = 1024 ~ 1000 = 10³
// 2²³ = 2¹⁰.2¹⁰.2³ ~ 10³.10³.8 = 8.10⁶ ~ 10⁷ 

void code_46() {
//	double a,b,c,d;
//	a = 1e-16;
	float a,b,c,d;
	a = 1e-8;
	b = a + 1.0;
	c = b - 1.0;
	d = (a + 1.0) - 1.0;
	if (c==a) printf("ok c\n"); 
		else  printf("pb c\n");
	if (d==a) printf("ok d\n"); 
		else  printf("pb d\n");
	printf("a = %36.30lf\n",a);
	printf("b = %36.30lf\n",b);
	printf("c = %36.30lf\n",c);
	printf("d = %36.30lf\n",d);
}
