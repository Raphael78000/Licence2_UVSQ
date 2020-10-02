#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *f = NULL;
	int c, n = 0;
	
	f = fopen(argv[1], "r");
	if (! f)
	{
		printf("wc: %s: No such file or directory\n", argv[1]);
		return 0;
	}
	c = fgetc(f);
	while (c != EOF)
	{
		n++;
		c = fgetc(f);
	}
	fclose(f);
	printf("%d %s\n", n, argv[1]);
	return 0;
}
