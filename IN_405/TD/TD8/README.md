% IN405 TD8 -- Systèmes d'exploitation
% Dictionnaire Pascal
% Raphael LAZZARI-ARMOUR 21920123 TD04B

# Contenu de l'archive
Cette archive est constituée des fichiers suivants :

- le fichier 'README.md', que vous êtes en train de lire ;
- le fichier 'client.c', fichier source contenant l'implémentation des fonctions côté client 
- le fichier 'server.c', fichier source contenant l'implémentation des fonctions côté serveur 
- le Makefile qui permet la compilation des fichiers, le nettoyage des exécutables ainsi que la compression des fichiers demandés en archive .tar 

# Utilisation
La compilation des fichiers doit se faire simplement à l'aide des commandes
ci-dessous :

```bash
$ make client 
$ make server 
```

ou bien de la commande suivante qui permet de compiler les deux fichiers : 

```bash
$ make all
```

L'utilisation, comme décrite dans l'énoncé du TD ainsi que dans les 'usage()'
des fichiers source 'client.c' et 'server.c', se fait comme ci-dessous :

```bash
création du serveur nommé 'math'
$ ./server math 4 &
ajout de la constante 'pi' avec pour valeur '3.14'
$ ./client math + pi 3.14
demande de valeur pour la constante 'pi'
$ ./client math ? pi
extinction du serveur 'math' qui va engendrer la suppression des tubes utilisés
$ ./client math !
```

Il est possible de modifier la localisation des tubes en remplaçant "/tmp" par la destination du répertoire souhaité dans chaque fichier à la ligne '#define DICT_PATH_PREFIX "/tmp"

# Quelques informations
Dans l'implémentation je me suis permis de rajouter quelques informations supplémentaires. Tout d'abord le serveur renvoie des informations sur chaque requête qu'il reçoit de la part du client, qu'elle soit fructueuse ou non.

J'ai également utilisé des fonctions non vus en cours mais qui ont été utiles dans la réalisation de ce TD. Les voici énoncés ci-dessous avec une rapide description de leur fonctionnement: 

- void* memset(void* pointer,int value,size_t count) -> "Cette fonction permet de remplir une zone mémoire, identifiée par son adresse et sa taille, avec une valeur précise." 
- double strtod(const char* theString,char** end) -> "Cette fonction, signifiant string to double, permet de transformer une chaîne de caractères, contenant la représentation textuelle d'un nombre flottant en une donnée typée double". 
- (const char* str1,const char* str2,size_t n) -> "Compare les n premiers bbites de str1 et str2, la fonction renvoie une valeur négative si les n premiers bites de str1 sont plus petits que str2, renvoie 0 si les n premiers bites de str1 et str2 sont égaux et renvoie une valeur positive si les n premiers bites de str2 sont plus petits que str1"
- char * strncpy( char * destination, const char * source, size_t length ) -> "Cette fonction permet de copier le contenu d'une chaîne de caractère dans une autre, dans la limite de 'length' caractères."
- void* memcpy( void * destination, const void * source, size_t size ) -> "Cette fonction permet de copier un bloc de mémoire spécifié par le paramètre source, et dont la taille est spécifiée via le paramètre size, dans un nouvel emplacement désigné par le paramètre destination."
