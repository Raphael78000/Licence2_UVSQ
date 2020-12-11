#include <stdio.h>
#include <stdlib.h>
#include "exo_40.h"

void afftailletype() {
	printf("+---------------+-----+\n");
	printf("|      Type     | nbo |\n");
	printf("+---------------+-----+\n");
	printf("| char          |  %2lu |\n",sizeof(char));
	printf("| unsigned char |  %2lu |\n",sizeof(unsigned char));
	printf("| short         |  %2lu |\n",sizeof(short));
	printf("| unsigned short|  %2lu |\n",sizeof(unsigned short));
	printf("| int           |  %2lu |\n",sizeof(int));
	printf("| unsigned int  |  %2lu |\n",sizeof(unsigned int));
	printf("| long          |  %2lu |\n",sizeof(long));
	printf("| unsigned long |  %2lu |\n",sizeof(unsigned long));
	printf("| long long     |  %2lu |\n",sizeof(long long));
	printf("+---------------+-----+\n");
	printf("| float         |  %2lu |\n",sizeof(float));
	printf("| double        |  %2lu |\n",sizeof(double));
	printf("| long double   |  %2lu |\n",sizeof(long double));
	printf("+---------------+-----+\n");

}
