#include <stdio.h>

void f(int x)
{
	x=x-1;
}

int g()
{
	int y;
	y=y+1;
	return y;
}

int main()
{
	int x,y;
	x=1;
	f(x);
	y=-1;
	g(y);


printf("x vaut : %d \n",x);
printf("y vaut : %d \n",y);

return 0;
}
