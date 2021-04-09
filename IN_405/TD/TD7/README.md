% IN405 TD7.2 -- Systèmes d'exploitation
% Protocole Phantom

# Instructions
- L'ouverture de deux terminaux est nécessaire :
- Dans le 1er, on compile avec la commande "gcc -o affichage affichage.c", puis on execute
avec la commande "./affichage"
- Dans le 2e, on compile avec la commande "gcc -o envoi envoi.c", puis on execute avec la 
commande "./envoi 'mode' 'pid' 'phrase'" :
	> Le mode est soit 0 (ce qui correspond à re-initialiser la liste de messages) avec au
	moins le pid derrière, soit 1 (pour ajouter un message dans la liste) avec au moins le
	pid et un message derrière.
	> Le pid s'affiche en premier lorsqu'on execute le programme 'affichage', il suffit de
	le recopier.
	> Le nombre d'arguments, suivant le mode et le pid, est seulement limité par une taille 
	de 1024 caractères et l'utilisation de symboles qui ne peuvent pas être lu correctement 
	dans le terminal (par exemple l'apostrophe), mais il est possible d'écrire une phrase 
	avec des espaces et des virgules.
- Faire ctrl+C dans le 1er terminal pour arreter l'affichage.
Ce programme peut recevoir jusqu'à 18 messages supplémentaires.
	
ATTENTION : N'oublier pas de changer le chemin défini dans l'en-tête des deux programmes pour
qu'il corresponde à votre environnement.
