#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


typedef unsigned char uint8_t;


#define SIZE 100
#define T1 10
#define T2 30


struct noeud
{
    struct noeud** suc;     // successeurs du noeud
    uint8_t vois;           // nombre de voisins
    uint8_t num;            // numéro du noeud : entre 1 et 100
    char* mes;              // message à transporter
};
typedef struct noeud** NOEUD;


struct Dij
{
    uint8_t pere;       // Père du i-ième sommet
    int distance;       // distance du i-ième sommet à la source
};


struct tab
{
    uint8_t mark[SIZE];          //tableau des sommets marqués
    uint8_t t[SIZE];            //tableau des sommets à traiter
    uint8_t top;                //le nombre de sommets à traiter
};


struct pile
{
    uint8_t Contenu[SIZE];
    uint8_t Taille;
};



/** Allocs and initialises an adjacency matrix
 *
 * @return	( uint8_t ) 	M 		a ready-to-use adjacency matric
 */
uint8_t** init_MA()
{
	uint8_t** M;

	M = malloc(sizeof(uint8_t*)*SIZE);
	if ( !M )
		return NULL;


	for ( int i = 1; i < SIZE; i++ )
	{
		M[i] = malloc(sizeof(uint8_t)*i);
		if ( !(M[i]) )
			return NULL;

		for ( int j = 0; j < i; j++ )
			M[i][j] = -1;
	}

	return M;
}


/** Prints out the adjacency matrix given through arguments
 *
 * @param ( uint8_t** ) 	M		Adjacency matrix to print
 */
void aff_MA ( uint8_t** M )
{
	int fd = open("./aff_MA", O_WRONLY | O_CREAT, 0777 );
	if ( fd == -1 )
		return;

	dprintf(fd, "Matrice adjecente du graphe :\n\n\n");

	dprintf(fd, "     | ");

	for ( int i = 0; i < SIZE; i++ )
		dprintf(fd, "s%3d | ", i);

	dprintf(fd, "\n");

	for ( int i = 0; i < SIZE; i++ )
	{
		dprintf(fd, "s%3d | ", i);
		for ( int j = 0; j < i; j++ )
			if ( M[i][j] == 255 )
				dprintf(fd, "     | ");
			else
				dprintf(fd, "%3d  | ", M[i][j]);

		dprintf(fd, " --\n");
	}

	close(fd);
}


/** Allocs and initialises a set of SIZE (struct noeud)
 *
 * @return	( NOEUD ) 	N 		a ready-to-use set of (struct noeud)
 */
NOEUD init_N ()
{
	NOEUD N;
	N = malloc(sizeof(struct noeud*)*SIZE);
	if ( !(N) )
		return NULL;

	for( int i = 0; i < SIZE; i++ )
	{
		N[i] = malloc(sizeof(struct noeud));
		if ( !(N[i]) )
			return NULL;

		N[i]->suc = NULL;
		N[i]->vois = 0;
		N[i]->num = i;
		N[i]->mes = NULL;
	}

	return N;
}


/** Prints out the set of (struct noeud) given through arguments
 *
 * @param ( NOEUD ) 	N		Set of (struct noeud) to print
 */
void aff_N ( NOEUD N )
{
	int fd = open("./aff_N", O_WRONLY | O_CREAT, 0777 );
	if ( fd == -1 )
		return;

	dprintf(fd, "Etats des noeuds :\n\n\n");

	for ( int i = 0; i < SIZE; i++ )
	{
		dprintf(fd, "s%3u      a", N[i]->num);
		dprintf(fd, "      %3u voisin(s) :     ",N[i]->vois);

		for (uint8_t j = 0; j < N[i]->vois; j++)
			dprintf(fd, "s%3u,   ", (N[i]->suc[j])->num);

		dprintf(fd, "\n");
	}

	close(fd);
}


/** Tells if P is a successor of S
 *
 * @param ( struct noeud* )		S		(struct noeud) to go through
 * @param ( struct noeud* )		P		(struct noeud) to compare with the successors of S
 *
 * @return		1 if P is a successor of S, 0 otherwise.
 */
int suc_in ( struct noeud* S, struct noeud* P)
{
	for ( int i = 0; i < S->vois; i++ )
		if ( (S->suc[i]) == P )
			return 1;

	return 0;
}


/** Indicates how many neighbours of a (struct noeud) is in a given tier
 *
 * @param ( struct noeud* )		N		(struct noeud) to go through
 * @param ( int )				Tier	Tier to check
 *
 * @return		O if Tier is not equal to 1, 2 or 3
 * 				the number of neighbours in Tier1 if Tier = 1
 * 				the number of neighbours in Tier2 if Tier = 2
 * 				the number of neighbours in Tier3 if Tier = 3
 */
int suc_tier ( struct noeud* N, int Tier )
{
	if ( Tier > 3 && Tier < 1 )
		return 0;

	int sum1 = 0, sum2 = 0, sum3 = 0;

	for ( int i = 0; i < N->vois; i++ )
		if ( (N->suc[i])->num < T1 )
			sum1++;
		else if ( (N->suc[i])->num < T2 )
			sum2++;
		else
			sum3++;

	switch ( Tier )
	{
		case 1 : return sum1;
		case 2 : return sum2;
		case 3 : return sum3;
		default : return 0;
	}
}


/** Writes a given value in the adjacency matrix
 *
 * @param ( uint8_t** )		M			The adjacency matric to write in
 * @param ( int )			i			Number of the column
 * @param ( int )			j			Number of the row
 * @param ( int )			val			Value to write
 */
void assign ( uint8_t** M, int i, int j, int val )
{
	if ( i < j )
		M[j][i] = val;
	else
		M[i][j] = val;
}


/** Assigns 2 (struct noeud)s as neighbours of each other
 *
 * @param ( NOEUD ) 	N 	    Set of (struct noeud) to manipulate
 * @param ( int ) 		n	 	index of the first (struct noeud) in N
 * @param ( int ) 		v       index of the first (struct noeud) in N
 */
void new_vois ( NOEUD N, int n, int v)
{
	N[n]->vois++;
	N[n]->suc = realloc(N[n]->suc, sizeof(struct noeud*)*N[n]->vois);
	N[n]->suc[N[n]->vois-1] = N[v];

	N[v]->vois++;
	N[v]->suc = realloc(N[v]->suc, sizeof(struct noeud*)*N[v]->vois);
	N[v]->suc[N[v]->vois-1] = N[n];
}


/** Takes care of the part of NOEUD N that belongs to Tier1
 *
 * @param ( uint8_t** )		M		Adjacency matric to modify
 * @param ( NOEUD ) 		N		Set of (struct noeud) to modify
 */
void Tier1 ( uint8_t** M, NOEUD N )
{
	int k, l;
	srandom(getpid());

	for( int i = 0; i < T1; i++ )
	{
		for( int j = 0; j < T1; j++ )
		{
			k = random()%4;

			if( k && (i != j) && !(suc_in(N[i], N[j])) )
			{
				l = random()%6 + 5;
				assign(M, i, j, l);
				new_vois(N, i, j);
			}
		}
	}
}


/** Takes care of the part of NOEUD N that belongs to Tier2
 *
 * @param ( uint8_t** )		M		Adjacency matric to modify
 * @param ( NOEUD ) 		N		Set of (struct noeud) to modify
 */
void Tier2 ( uint8_t** M, NOEUD N )
{
	int r1, r2;
	int k, l;
	srandom(getpid());

	for( int i = T1; i < T2; i++ )
	{
		r1 = random()%2 + 1;

		for( int j = 0; j < r1; j++ )
		{
			k = random()%T1;

			if( !(suc_in(N[i], N[k])) )
			{
				l = random()%11 + 10;
				assign(M, i, k, l);
				new_vois(N, i, k);
			}
			else
				j--;
		}

		for( int j = suc_tier(N[i], 2); j < 2; j++)
		{
			k = random()%(T2-T1) + T1;

			if( (i != k) && !(suc_in(N[i], N[k])) && (suc_tier(N[k], 2) < 3) )
			{
				l = random()%11 + 10;
				assign(M, i, k, l);
				new_vois(N, i, k);
			}
			else
				j--;
		}

		r2 = random()%4;

		if ( r2 == 0 )
		{
			k = random()%(T2-T1) + T1;
			if( (i != k) && !(suc_in(N[i], N[k])) && (suc_tier(N[k], 2) < 3) && (suc_tier(N[i], 2) < 3) )
			{
				l = random()%11 + 10;
				assign(M, i, k, l);
				new_vois(N, i, k);
			}
		}
	}
}


/** Takes care of the part of NOEUD N that belongs to Tier3
 *
 * @param ( uint8_t** )		M		Adjacency matric to modify
 * @param ( NOEUD ) 		N		Set of (struct noeud) to modify
 */
void Tier3 ( uint8_t** M, NOEUD N )
{
	int k, l;
	srandom(getpid());

	for( int i = T2; i < SIZE; i++ )
	{
		for( int j = 0; j < 2; j++ )
		{
			k = random()%(T2-T1) + T1;

			if( !(suc_in(N[i], N[k])) )
			{
				l = random()%36 + 15;
				assign(M, i, k, l);
				new_vois(N, i, k);
			}
			else
				j--;
		}

		for( int j = suc_tier(N[i], 3); j < 1; j++ )
		{
			k = random()%(SIZE-T2) + T2;

			if( (i != k) && !(suc_in(N[i], N[k])) && (suc_tier(N[k], 3) == 0)  )
			{
				l = random()%36 + 15;
				assign(M, i, k, l);
				new_vois(N, i, k);
			}
			else
				j--;
		}
	}
}


void explorer( struct noeud* N, uint8_t* b )
{
	b[N->num] = 1;

	for( int j = 0; j <= N->vois-1; j++)
		if( b[(N->suc[j])->num] == 0 )
			explorer(N->suc[j], b);
}


int ParcoursProfondeur(NOEUD N)
{
	int somme = 0;
	uint8_t* b;
	b = malloc(sizeof(uint8_t)*SIZE);

	for ( int i = 0; i < SIZE; i++ )
		b[i] = 0;

	explorer(N[0], b);

	for ( int i = 0; i < SIZE; i++ )
		somme += b[i];

	free(b);
	return somme;
}


int Connexite(NOEUD N)
{
	int NoeudMarque = ParcoursProfondeur(N);

    return NoeudMarque == SIZE;
}


/** Checks if all the notes of the graph has been treated
 *
 * @param ( uint8_t** M ) Adjacency matric that represents the graphe
 *
 * @return 1 is return if all note has been treated or 0 is return if not
 */
int Tous_Marque(struct tab* T)
{
    for (int i = 0; i < SIZE; i++ )
        if ( T->mark[i] == 0 ) return 0;

    return 1;
}

/** function that returns the value of the ridge between two notes
*
* @param (uint8_t** M) Adjacency matric that represents the graphe
* @param (int i) source note
* @param (int j) destination note
*
* @return the value of the ridge between note i and note j
*/
uint8_t poids(uint8_t** M,uint8_t i,uint8_t j)
{
    if ( i < j )
        return M[j][i];
    else
        return M[i][j];
}

/**
* function that stacks an element
*/
void empiler(struct pile* P,uint8_t new)
{
    if ( P->Taille >= SIZE )
        return;

    P->Contenu[P->Taille] = new;
    P->Taille++;
}


/**
* function that unstacks an element and returns the element unstacked
*/
uint8_t depiler(struct pile* P)
{
	P->Taille--;
    uint8_t rc = P->Contenu[P->Taille];
    return rc;
}


uint8_t renvoie_minimum ( struct tab* T, struct Dij* D )
{
	int k;
	int min = 9999;
	uint8_t sommet = -1;

	if ( T->top == 0 ) printf("tableau vide\n");

	for( int i = 0; i < T->top; i++ )
	{
		if ( D[T->t[i]].distance < min )
		{
			min =  D[T->t[i]].distance;
			sommet = T->t[i];
			k = i;
		}
	}

	for( int j = k; j < T->top-1; j++ )
		T->t[j] = T->t[j+1];

	T->t[T->top] = -1;
	T->top--;
	T->mark[sommet] = 1;
	return sommet;
}


void ajouter_tableau ( struct tab* T, uint8_t new  )
{
	for( int i = 0; i < T->top; i++ )
		if ( T->t[i] == new )
			return;

	T->t[T->top] = new;
	T->top++;
}


/** calculates the shortest path between source note and all the other notes of the graph
*
* @param (uint8_t** M) Adjacency matric represents the graph
* @ param (Noeud N)   original graph
* @param (int source) source note form which we want to calculate the shortest path to all the other notes of graph
*
* @return a 2D tab with the shortest path notes between source note and each other notes of the graph
*/
uint8_t** Dijkstra(uint8_t** M,NOEUD N,int source)
{
    struct Dij* D;
    D = malloc(sizeof(struct Dij)*SIZE);

    struct tab* T;
    T = malloc(sizeof(struct tab));

    int current;

    for (int i = 0; i < SIZE; i++ )
    {
        D[i].pere = -1;
        D[i].distance = 9999;
        T->mark[i] = 0;
        T->t[i] = -1;
    }

    T->top = 0;
    D[source].distance = 0;
    ajouter_tableau(T, source);

    while ( !Tous_Marque(T) )
    {
        current = ( int ) renvoie_minimum(T, D);

        for ( int i = 0; i < N[current]->vois; i++ )
        {
            if ( (poids(M, current, (N[current]->suc[i])->num) + D[current].distance) < D[(N[current]->suc[i])->num].distance )
            {
                D[(N[current]->suc[i])->num].distance = poids(M, current, (N[current]->suc[i])->num) + D[current].distance;
                D[(N[current]->suc[i])->num].pere = current;
            }

            if ( T->mark[(N[current]->suc[i])->num] == 0 )
                    ajouter_tableau(T, (N[current]->suc[i])->num);
        }
    }

    uint8_t** A;
    A = malloc(sizeof(uint8_t*)*SIZE);

    for ( int i = 0; i < SIZE; i++ )
    {
        if ( i == source )
            A[i] = NULL;
        else
        {
            struct pile p;
            p.Taille = 0;
            uint8_t j = i;

            while( j != source )
            {
                empiler(&p, j);
                j = D[j].pere;
            }

            A[i] = malloc(sizeof(uint8_t)*p.Taille);

            for ( j = 0; p.Taille != 0; j++ )
				A[i][j] = depiler(&p);
        }
    }

    free(D);
    free(T);

    return A;
}


uint8_t*** Tables_Routages(uint8_t** M,NOEUD N)
{
    uint8_t*** A;
    A = malloc(sizeof(uint8_t**)*SIZE);

    for (int i = 0; i < SIZE; i++ )
		A[i] = Dijkstra(M, N, i);

    return A;
}

void print_parcours( uint8_t* TR, uint8_t source, uint8_t target )
{
    printf("\nOn part du sommet %u -> ", source );

    for ( int i = 0; TR[i] != target; i++ ) printf("sommet %u  ->   ", TR[i]);

    printf("sommet %u  \n", target);
}


/** Frees a set of (struct noeud)
 *
 * @param ( NOEUD ) 	N		Set of (struct noeud) to free
 */
void free_N ( NOEUD N )
{
	for( int i = 0; i < SIZE; i++ )
	{
		free(N[i]->suc);
		free(N[i]);
	}

	free(N);
}


/** Frees an adjacency matrix
 *
 * @param ( uint8_t** ) 	M		Adjacency matrix to free
 */
void free_MA( uint8_t** M )
{
	for ( int i = 1; i < SIZE; i++ )
		free(M[i]);

	free(*M);
}


void free_Tables_Routages ( uint8_t*** A )
{
    for ( int i = 0; i < SIZE; i++ )
    {
        for ( int j = 0; j < SIZE; j++ )
            if ( i != j ) free(A[i][j]);

        free(A[i]);
    }
    free(A);
}


void main()
{
	NOEUD N;
	uint8_t** M;
	uint8_t*** T;

	printf("\nInitialisation du graphe...\n\n");

	M = init_MA();
  	N = init_N();
  	Tier1(M, N);
  	Tier2(M, N);
  	Tier3(M, N);

	while ( !Connexite(N) )
	{
		free_MA(M);
		free_N(N);
		M = init_MA();
		N = init_N();
		Tier1(M, N);
		Tier2(M, N);
		Tier3(M, N);
	}

	 printf("Tables de routage en cours de création...\n");

	 T = Tables_Routages(M,N);

	 while ( 1 )
	 {
		char source[16], destination[16];
		int i, j;

		printf("\nDe quel sommet voulez-vous partir ?\n\n");
		scanf("%s", source);

		if ( !strcmp(source, "quit") )
			goto quit;
		else
			i = atoi(source);

		printf("\nQuel sommet voulez-vous atteindre?\n\n");
		scanf("%s", destination);

		if ( !strcmp(destination, "quit") )
			goto quit;
		else
			j = atoi(destination);

		if ( i == j )
			printf("\nIl n'y a pas de chemin entre un sommet et lui-même\n");
		else
			print_parcours(T[i][j] , i, j);
	}


	quit:

	free_N(N);
	free_MA(M);
	free_Tables_Routages(T);
}
