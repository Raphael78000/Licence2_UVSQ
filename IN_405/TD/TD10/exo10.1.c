#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// Enumération des différents opérateurs possibles
typedef enum {
	OCD_SOMME,
	OCD_MOYENNE,
	OCD_MAX,
	OCD_MIN,
	OCD_TOTAL
} opcode_t;

// Structure contenant les arguments du programme
typedef struct {
	int nbThreads;			//< Nombre de threads à utiliser
	int tailleTableau;		//< Taille du tableau utilisé pour la réduction
	opcode_t code;			//< Opération à réaliser
} arg_t;

// Structure contenant les informations nécessaires au thread
typedef struct {
	int* tab;				//< Tableau d'entiers à traiter
	int beg;				//< Indice de début de traitement
	int end;	        	//< Indice de fin de traitement (non compris)	
	int res;				//< Résultat local					
} message_t;

// Alias de pointeurs de fonction
typedef int (* ptrVerif) (int *, int, int);

// Fonction thread -- calcule la somme locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * sommeTableau (void * arg)
{
	message_t* mes = (message_t*) arg;
	
	int sum = 0;
	int i;
	
	for( i = mes->beg; i < mes->end; i++ )
		sum += mes->tab[i];
		
	mes->res = sum;
	
	printf("Somme du partielle tableau = %d\n", sum);
	return NULL;
}

// Fin de la réduction -- calcule la somme globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducSomme (message_t * mes, int nbThreads) 
{
	int sum = 0;
	int i;
	
	for( i = 0; i < nbThreads; i++ )
		sum += mes[i].res;
		
	printf("Somme du tableau = %d\n", sum);
	return sum;
}

// Fonction thread -- calcule la moyenne locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * moyenneTableau (void * arg) 
{
	message_t* mes = (message_t*) arg;
	
	int moy = 0;
	int i;
	
	for( i = mes->beg; i < mes->end; i++ )
		moy += mes->tab[i];
		
	moy /= i-1;
	mes->res = moy;
	
	printf("Moyenne partielle du tableau = %d\n", moy);
	return NULL;
}

// Fin de la réduction -- calcule la moyenne globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMoyenne (message_t * mes, int nbThreads) 
{
	int moy = 0;
	int i;
	
	for( i = 0; i < nbThreads; i++ )
		moy += mes[i].res;
		
	moy /= nbThreads-1;
	
	printf("Moyenne du tableau = %d\n", moy);
	return moy;
}

// Fonction thread -- calcule le maximum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * maxTableau (void * arg) 
{  
	message_t* mes = (message_t*) arg;
	
	int max = mes->tab[mes->beg];
	
	for( int i = mes->beg+1; i < mes->end; i++ )
		max = (max < mes->tab[i])?(mes->tab[i]):(max);
		
	mes->res = max;
	printf("Maximum partiel du tableau = %d\n", max);
	return NULL;
}

// Fin de la réduction -- calcule le maximum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMax (message_t * mes, int nbThreads) 
{
	int max = mes[0].res;
	
	for( int i = 1; i < nbThreads; i++ )
		max = (max < mes[i].res)?(mes[i].res):(max);
	
	printf("Maximum du tableau = %d\n", max);
	return max;
}

// Fonction thread -- calcule le minimum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * minTableau (void * arg) 
{  
	message_t* mes = (message_t*) arg;
	
	int min = mes->tab[mes->beg];
	
	for( int i = mes->beg+1; i < mes->end; i++ )
		min = (min > mes->tab[i])?(mes->tab[i]):(min);
	
	mes->res = min;
	printf("Minimum partiel du tableau = %d\n", min);
	return NULL;
}

// Fin de la réduction -- calcule le minimum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMin (message_t * mes, int nbThreads) 
{
	int min = mes[0].res;
	
	for( int i = 1; i < nbThreads; i++ )
		min = (min > mes[i].res)?(mes[i].res):(min);

	printf("Minimum du tableau = %d\n", min);
	return min;
}

// NE PAS TOUCHER
// Fonction de vérification -- somme des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifSomme (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- moyenne des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMoyenne (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	if (tailleTableau == 0)
		return resultat == 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == (tmp / tailleTableau);
}

// NE PAS TOUCHER
// Fonction de vérification -- maximum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMax (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp < tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- minimum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMin (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 101;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp > tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// Analyse des arguments du programme. Quitte si le nombre d'arguments est
// différent de 4. Remplit la structure de données des arguments.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Structure de données des arguments
arg_t analyseArguments (int argc, char ** argv) 
{  
	if( argc != 4)
	{
		printf("Le nombre d'argument n'est pas correct.\n");
		exit(0);
	}

	arg_t a;
	
	a.nbThreads = atoi(argv[1]);
	a.tailleTableau = atoi(argv[2]);
	switch (argv[3][0])
	{
			case '+' : a.code = OCD_SOMME;
					   break;
			case '/' : a.code = OCD_MOYENNE;
					   break;
			case 'M' : a.code = OCD_MAX;
					   break;
			case 'm' : a.code = OCD_MIN;
					   break;
			default : printf("op non reconnue\n");
					  exit(0);
	}
	return a;
}

// NE PAS TOUCHER
// Récupération de la fonction de vérification à partir de l'opcode
// \param	opcode 			Code de l'opération
// \return					Pointeur de la fonction de vérification
ptrVerif decodeOpcodeVerif (const opcode_t o) {
	switch (o) {
		case OCD_SOMME:		return verifSomme;
		case OCD_MOYENNE:	return verifMoyenne;
		case OCD_MAX:		return verifMax;
		case OCD_MIN:		return verifMin;
		default:
			printf ("L'opération n'a pas été reconnue\n");
			exit (-1);
	}
}

// Génération du tableau avec des entiers compris entre 1 et 100.
// \param	tailleTableau	Taille du tableau d'entiers
// \return					Tableau d'entiers
int * genereTableau (int tailleTableau) 
{  
	int* tab;
	tab = malloc(sizeof(int)*tailleTableau);
	
	for ( int i = 0; i < tailleTableau; i++ )
		tab[i] = random()%100+1;
		
	return tab;
}

// Fonction chargée de la réduction multi-threadé, elle va initialiser les
// différentes variables utilisées par les threads (tableau d'entier, messages,
// etc.) puis créer les threads. Une fois l'exécution des threads terminée et
// la réduction opérée, la vérification du résultat est faite.
// \param	arg 			Arguments du programme décodés
void programmePrincipal (const arg_t arg) 
{
	// Déclaration des variables
	int * tab, res;
	pthread_t * th;
	message_t* mes;
	message_t* mes_fin;
	pthread_mutex_t* mutex;

	// Allocation de la mémoire
	th = malloc(sizeof(pthread_t)*arg.nbThreads);
	mes = malloc(sizeof(message_t)*arg.nbThreads);
	mes_fin = malloc(sizeof(message_t));
	mutex = malloc(sizeof(pthread_mutex_t));
	
	// Initialisation des variables et création des threads
	pthread_mutex_init(mutex, NULL);
	tab = genereTableau(arg.tailleTableau);
	mes_fin->tab = tab;
	mes_fin->beg = 0;
	mes_fin->end = arg.tailleTableau;
	
	if ( arg.code == OCD_MIN )
		mes_fin->res = 100;
	else
		mes_fin->res = 0;


	for( int i = 0; i < arg.nbThreads; i++ )
	{
		mes[i].tab = tab;
		mes[i].beg = (int) ((arg.tailleTableau*i)/arg.nbThreads);
		mes[i].end = (int) ((arg.tailleTableau*(i+1))/arg.nbThreads);
		
		switch ( arg.code )
		{
			case OCD_SOMME : pthread_create(&(th[i]), NULL, sommeTableau, (void*) &(mes[i]));
					   break;
			case OCD_MOYENNE : pthread_create(&(th[i]), NULL, moyenneTableau, (void*) &(mes[i]));
					   break;
			case OCD_MAX : pthread_create(&(th[i]), NULL, maxTableau, (void*) &(mes[i]));
					   break;
			case OCD_MIN : pthread_create(&(th[i]), NULL, minTableau, (void*) &(mes[i]));
					   break;
			default : printf("op non reconnue\n");
					  return;
		}
	}
		
	// Jointure
	
	for( int i = 0; i < arg.nbThreads; i++ )
				pthread_join(th[i], NULL);
				
	for( int i = 0; i < arg.nbThreads; i++ )
	{
		pthread_mutex_lock(mutex);

		switch ( arg.code )
		{
				case OCD_SOMME : mes_fin->res += mes[i].res;
						   break;
				case OCD_MOYENNE : mes_fin->res += mes[i].res/arg.nbThreads;
						   break;
				case OCD_MAX : mes_fin->res = (mes_fin->res < mes[i].res)?(mes[i].res):(mes_fin->res); 
						   break;
				case OCD_MIN :  mes_fin->res = (mes_fin->res < mes[i].res)?(mes_fin->res):(mes[i].res);
						   break;
				default : printf("op non reconnue\n");
						  return;
		}
		pthread_mutex_unlock(mutex);
	}
	
	printf("Résultats : %d\n", mes_fin->res);
	

	// NE PAS TOUCHER
	if ( (* (decodeOpcodeVerif (arg.code) ) ) (tab, arg.tailleTableau, mes_fin->res) )
		printf ("Le resultat est juste.\n");
	else printf ("Le resultat est faux.\n");
	// FIN

	// Libération de la mémoire
	free(tab);
	free(mes);
	free(mes_fin);
	free(th);
	pthread_mutex_destroy(mutex);
	free(mutex);
}

// NE PAS TOUCHER
// Fonction main -- analyse les arguments donnés au
// programme, puis exécute le programme principal, chargé de la réduction
// multi-threadée.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Code de retour du programme (0 en cas de réussite)
int main (int argc, char ** argv) {
	arg_t a;

	srand (time (NULL) );

	a = analyseArguments (argc, argv);
	programmePrincipal (a);
	
	return 0;
}
