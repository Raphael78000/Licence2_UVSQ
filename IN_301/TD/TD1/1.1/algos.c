#include "constantes.h"

int T[N];

void lecture()
{
	FILE *f = NULL;
	int i;
	
	f = fopen(NOMFIC, "r");
	for (i = 0; i < N; i++)
	{
		if (! f)
			T[i] = 0;
		else if (fscanf(f, "%d", &T[i]) == EOF)
		{
			fclose(f);
			f = NULL;
		}
	}
}

void ecriture()
{
	FILE *f;
	
	f=fopen("nombres-verif.data","w");
	
	for (int i=0;i<N;i++)
	{
		fprintf(f,"%6d\n",T[i]);
	}
	fclose(f);
}

int recherche(int x)
{
	int i = 0;
	
	while (i < N && T[i] != x)
		i++;
	printf("comparaisons = %d\n", i + 1);
	return (i < N) ? 1 : 0;
}

int stat_recherche(int x)
{
	int i = 0;
	
	while (i < N && T[i] != x)
		i++;
		
	return i + 1;
}

int main()
{
	int c = 0, i = 0;
	
	srand(getpid());
	lecture();
	ecriture();
	while (i < N)
	{
		c = stat_recherche(rand() % 5 * MAX);
		printf("%d\n",c);
		i++;
	}
	printf("Moyenne comparaisons = %d\n", c / i);
	
	return 0;
}
