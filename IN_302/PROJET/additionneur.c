#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//affiche l'écriture binaire héxadécimal dans le terminal
void afficher_tab(char* s){
  for (int i = 0; i < 16; i++){
    printf("%c ",s[i]);
  }
  printf("\n");
}

//convertit un nombre décimal (16bits) en son binaire sotcké dans un tableau (16 bits)
char* convert_dec_bin(int n,char* tab){
  for (int i = 15; i >= 0; i--){	//commence la conversion en convertissant 
    if (n % 2) tab[i] = '1';			//du bit le moins fort au bit le plus fort 
    else tab[i] = '0';
    n = n / 2;
  }
  return tab;
}

//permet de convertir les valeurs entrées par l'utilisateur en entrée
int convertir_entree(char* tab,char* strhexa){
  int dec;//contiendra la valeur en décimal du nombre héxadécimal entré par l'utilisateur
  char* ptr;//contient la chaîne de caractère si elle a été saisie par l'utilisateur(ne prends pas "0x")

  dec = strtol(strhexa,&ptr,16);//renvoie le nombre présent dans une chaine caractere et stock une chaine char saisite dans ptr 

  if (dec > 65535){//return 1 dans le cas où l'héxadécimal ne tient pas sur 16 bits 
    printf("nombre hexadecimal ne tient pas sur 16 bits\n");
    return 1;
  }
  if (ptr[0] != '\0'){//retourne 1 dans le cas où l'utilisateur a rentré une chaine de caractere lors de la saisie 
    printf(" un parametre ne represente pas une valeur hexadecimale\n");
    return 1;
  }
  tab = convert_dec_bin(dec,tab);
  return 0;
}

//porte universelle logique NON-ET
char pl_NAND(char a,char b){
  if (a=='1' && b=='1') return '0';
  else return '1';
}

//porte universelle logique NON-OU
char pl_NOR(char a,char b){
  if (a=='0' && b=='0') return '1';
  else return '0';
}

//porte logique OU exclusif
char pl_XOR(char a,char b){
  char c,d,e;
  c = pl_NAND(a,b);										//le nombre d'appel à la fonction NOR est
  d = pl_NAND(a,c);										//le même que la fonction NAND,
  e = pl_NAND(c,b);										//le shcéma est exactement le même
  return pl_NAND(d,e);
}

//porte logique ET
char pl_AND(char a,char b){
  char c;															//appelle de 2 fois la fonction NAND 
  c = pl_NAND(a,b);										//comparé à 3 fois pour la fonction NOR
  return pl_NAND(c,c);
}

//porte logique OU
char pl_OR(char a,char b){
  char c;														//appelle de 2 fois la fonction NOR 
  c = pl_NOR(a,b);									//comparé à 3 fois pour la fonction NAND
  return pl_NOR(c,c);
}

//porte logique NON
char pl_NOT(char a){
  return pl_NOR(a,a);								//même complexité pour l'utilisation
}																	//des 2 portes logiques universelles

//addition de 2 bits en tenant compte du report précédent et renvoie l'overflow si il y en a un
char add_1b(char a,char b,char Cin,char* Cout){
  char c,d,e; //contient le résultat des différentes portes logiques utilisées à travers le programme

  //1ere étape
  c = pl_XOR(a,b);
  d = pl_AND(a,b);

  //2eme étape
  e = pl_AND(c,Cin);

  //retourne le nouveau report
  *Cout = pl_OR(e,d); // *Cout car (Cout) contiendra l'adresse de la variable donné en paramètre
										//donc mettre valeur pl_OR(e,d) dans l'adresse donné en paramètre nécessite '*' devant Cout
  return pl_XOR(c,Cin);//retourne la somme des 3 bits -> a + b + Cin (le report de l'addition précédente)
}

//additionne les bits de 2 nombres de 16 bits
char add_16b(char* a,char* b,char* sum){					//la fonction renvoie '1' dans le cas où l'addition des 2 nombres binaires 
  char over = 0;//initialisation overflow à 0 					//à produit un overflow, sinon renvoie '0'

  for (int i = 15; i >= 0;i--){												//effectue le calcul en commençant par le bit le moins fort des 2 nombres 
    sum[i] = add_1b(a[i], b[i], over, &over);						//et re monte vers le but le plus fort tout en le stockant dans un autre tableau
  }
  return over;
}

//convertit un nombre représenté sous sa forme binaire dans un tableau en sa valeur decimal
int convert_bin_dec(char* s){
  int dec = 0; //Initialise le nombre à 0
  int n; // retranscrit int = 1 si valeur '1' croisée ou int =0 si valeur '0' croisée
  int count = 0;//va nous permettre de savoir à quelle puissance élevé le bit lors du parcours du tableau
  
  for (int i = 15; i >= 0; i--){			//on part du bit le moins fort pour remonter au bit le plus fort 
        if (s[i]=='1') n = 1; 					
			else n = 0;
        dec = dec + (n * pow(2,count)); //calcul le bit à la puissance nécessaire 
        count++;										//à chaque instant du parcours du tableau
    }
    return dec;
  }

int main(int argc, char** argv){
  char s1[16];//contient le 1er nombre hexadecimal en binaire (penser a rajouter 1 pour le caractere '\0' fin de chaîne)
  char s2[16];//contient le 2eme nombre hexadecimal en binaire (penser a rajouter 1 pour le caractere '\0' fin de chaîne)
  char s3[16];//contient le résultat de l'addition des 2 nombres
  char over_f;//contient '0' si pas d'overflow et contient '1' si overflow

  //Si l'utilisateur inscrit une seule valeur ,ou 3,4,5,6,etc valeurs le programme s'arrête et renvoie 1
  if (argc != 3){
    printf("2 parametres sont a inscrire \n");
    return 1;
  }

  if (convertir_entree(s1,argv[1])==0){		//ecrit le nombre hexadecimal sous sa forme binaire,retourne 0 si la 
     printf("binaire valeur 1 : ");						//conversion s'est bien pasée, retourne 1 dans le cas contraire
     afficher_tab(s1);											
   }																		
   else{
     return 1;
   }
  if (convertir_entree(s2,argv[2])==0){		//ecrit le nombre hexadecimal sous sa forme binaire, retourn 0 si la 
     printf("binaire valeur 2 : ");						//conversion s'est bien pasée, retourne 1 dans le cas contraire
     afficher_tab(s2);
   }
   else{
     return 1;
   }

   over_f = add_16b(s1,s2,s3);//calcul l'addition des deux nombres binaires rentrées en paramètres et renvoie overflow
   
	//donne l'affichage du résultat de l'addition des deux nombres sous forme héxadécimal et sous forme binaire
   printf("\nLe resultat de l addition sous forme hexadecimal est: 0x%x\n",convert_bin_dec(s3));
   printf("son overflow est : %c\n",over_f);
   printf("son resultat en binaire est : ");
   afficher_tab(s3);

	//le code renvoie 0 si les conversions se sont bien passées
	//retourne 1 dans le cas où les conversions des deux nombres se sont pas passées correctement 
  return 0;
}
