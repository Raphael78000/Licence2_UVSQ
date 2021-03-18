% IN405 TD4 -- Systèmes d'exploitation
% Protocole Phantom

@author Raphael LAZZARI-ARMOUR 21920123
@version 18/03/2021

# Contenu de l'archive
Cette archive est constituée des fichiers suivants :

- README.md : fichier décrivant le contenu de l'archive ;
- main.c : fichier source principale du projet, contenant la fonction main()
  du programme ;
- api.h : fichier d'en-tête décrivant les deux appels principaux de l'API, un
  pour récupérer le contenu de la hiérarchie à "copier", et un second pour
  créer un répertoire "phantom", copiant les méta-données de la hiérarchie
  "copiée" ;
  
- api.c : fichier source contenant les fonctions définies dans le fichier api.h;
- internals.h : fichier d'en-tête décrivant les appels de base utilisés par
  l'API qui seront testés unitairement;
- internals.c: fichier source contenant les fonctions définies dans le fichier 
 internals.h;
- Makefile : matériel de compilation basique

# Instructions d'utilisation
Pour compiler le code, l'utilisateur devra rentrer la commande "make" dans le terminal,
un éxécutable "phantom" sera crée.

Afin d'éxécuter le programme, l'utilisateur devra rentrer dans le terminal la ligne
de commande suivante: ./phantom  répertoire_source répertoire_destination

-> Uniquement les fichiers réguliers, les répertoires et liens symboliques seront prit 
   en compte dans le répertoire source afin d'en faire une copie "phantom"

Le programme effectue donc une copie parfaite en apparence du répertoire source
dans le répertoire destination. La copie ne sera pas parfaitement identique au répertoire
source puisque les fichiers réguliers copiés seront identiques en apparence mais pas 
en leur contenu. 

Afin que la taille des fichiers réguliers soit identique, le programme remplit le fichier 
du char 'a' jusqu'à obtenir la même taille que le fichier souhaité dans le répertoire source
Le choix de l'écriture d'un char s'est fait car un char occupe une place de un octet, donc cela 
permet d'écrire jusqu'à obtenir la taille identique que le fichier souhaité. Ce qui n'est pas possible
avec un int qui occupe 2 octets (processeur 16bits) ou 4 octets (processeur 32bits) suivant le 
processeur utilisé par l'ordinateur.

Pour effectuer la supression des fichiers de compilation (*.o), l'utilisateur devra rentrer la commande 
"make clean"

La commande "make tar" permet d'effectuer une archive au format .tar comprenant l'ensemble des fichiers
à extension .c .h ainsi que le README.md (fichier actuel) et le Makefile

# Remontée de bugs
Lors de la réalisation du TD, j'ai effectué l'allocation de mémoire de l'élèment suivant de la struct file 
avant d'accéder au prochain élèment. Ceci a pour effet que lorsque le programme arrive sur le dernier élèment
d'un répertoire, la mémoire de l'élèment suivant est allouée par défaut. Cela a pour conséquence que la liste
chaînée occupe une taille de plus que le nombre d'élèement présent dans le répertoire. Pour remédier à cela, 
j'ai crée une fonction "organize_struct(struct file* fichier)" qui permet de supprimer le dernier élèment de la 
liste chaînée qui ne contient aucune donnée, car il s'agit d'une zone mémoire allouée mais non remplit et donc 
que l'on n'utilise pas. 

Cela a pour conséquence de rajouter une compléxité de l'ordre O(n) à chaque parcours de la fonction 
"browse_directory(const char *path, struct file **current)".
