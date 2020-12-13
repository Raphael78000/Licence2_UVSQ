#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//affiche l'écriture binaire héxadécimal dans le terminal
void afficher_tab(char* s){
  for (int i = 0; i < 16; i++){
    printf("%c ",s[i]);
  }
  printf("\n");
}

//convertit un héxadécimal en son binaire sur 4 bits
char* hex_to_bin(char c){

  switch (c){
    case '0': return  "0000"; case '1': return  "0001";
    case '2': return  "0010"; case '3': return  "0011";
    case '4': return  "0100"; case '5': return  "0101";
    case '6': return  "0110"; case '7': return  "0111";
    case '8': return  "1000"; case '9': return  "1001";
    case 'a': return  "1010"; case 'b': return  "1011";
    case 'c': return  "1100"; case 'd': return  "1101";
    case 'e': return  "1110"; case 'f': return  "1111";
  }
}

//fonction qui test si la valeur entrée est un hexadecimal et si l'hexadecimal rentre dans 16bits
int est_hexadecimal_16bit(char* valeur){
  if (valeur[0] != '0' && valeur[1] != 'x'){
    printf("Vous avez pas entre un nombre hexadecimal\n");
    return 0;
  }
  if (strlen(valeur+2) > 4){
    printf("le nombre hexadecimal saisit ne peut pas etre represente sur 16 bits");
    return 0;
  }
  return 1; //(valeur+2) permet d'enlever la notation "0x" et de tenir compte que du nombre hexadecimal
}

//il nous faut obtenir une chaîne à 4 valeurs afin d'éviter les erreurs d'écriture
char* pb_lecture_hexa(char* s){
  char* z;//va contenir le nombre hexadecimal corrigé à la fini
  int j = 0;

  for (int i = 0; i < (4 - strlen(s)); i++) z[i] = '0';         //nous permet de placer des '0' si besoin avant la chaîne s si besoin
  for (int i = (4 - strlen(s)); i < 4; i++) z[i] = s[j]; j++;  //pour atteindre une chaîne à 4 valeurs en fin fonction
  return z;//retourne le nombre hexadécimal coorect pour que la suite de sa conversion puisse fonctionner
}

//fonction qui convertit l'héxadecimal en binaaire stocké dans un tableau
int convertir_entree(char* tab,char* strhexa){
  if (est_hexadecimal_16bit(strhexa)){
    return 0;
}
  char* s = strhexa + 2; //permet d'avoir le nombre hexadecimal sans la notation "0x"
  if (strlen(s) < 4){
    s = pb_lecture_hexa(s);
  }
  char* z; //permet de stocker temporairement la conversion d'une valeur hexadecimal en binaire
  int count = 0;

  for (int i = 0; i < 4; i++){
  z = hex_to_bin(s[i]);
    for (int j = 0; j < 4; j++){
      tab[count] = z[j];
      count++;
    }
  }
  return 1;
}

//porte universelle logique
char pl_NAND(char a,char b){
  if (a=='1' && b=='1') return '0';
  else return '1';
}

//porte universelle logique
char pl_NOR(char a,char b){
  if (a=='0' && b=='0') return '1';
  else return '0';
}

//le nombre appelle à la fonction NOR est le même que la fonction NAND, le shcéma est exatcement le même
char pl_XOR(char a,char b){
  char c,d,e;
  c = pl_NAND(a,b);
  d = pl_NAND(a,c);
  e = pl_NAND(c,b);
  return pl_NAND(d,e);
}

//appelle de 2 fois la fonction NAND comparé à 3 fois pour la fonction NOR
char pl_AND(char a,char b){
  char c;
  c = pl_NAND(a,b);
  return pl_NAND(c,c);
}

//appelle de 2 fois la fonction NOR comparé à 3 fois pour la fonction NAND
char pl_OR(char a,char b){
  char c;
  c = pl_NOR(a,b);
  return pl_NOR(c,c);
}

//même complexité pour l'utilisation des 2 portes logiques universelles
char pl_NOT(char a){
  return pl_NOR(a,a);
}

//addition de 2 bits en tenant compte du report précédent
char add_1b(char a,char b,char Cin,char* Cout){
  char c,d,e;

  //1ere étape
  c = pl_XOR(a,b);
  d = pl_AND(a,b);

  //2eme étape
  e = pl_AND(c,Cin);

  //retourne le nouveau report
  *Cout = pl_OR(e,d); //*Cout car Cout contiendra l'adresse donné en paramètre
                        //donc mettre valeur pl_OR(e,d) dans l'adresse donné en paramètre nécessite '*' devant Cout
  return pl_XOR(c,Cin);//retourne la somme des 3 bits -> a + b + Cin (le report de l'addition précédente)
}

//addition de 2 nombres de 16 bits
char add_16b(char* a,char* b,char* sum){
  char over = 0;//initialisation overflow à 0

  for (int i = 15; i >= 0;i--){
    sum[i] = add_1b(a[i], b[i], over, &over);
  }
  return over;
}

int convert(char* s){
  int dec = 0;
  int n;
  int count = 0;
  for (int i = 15; i >= 0; i--){
        if (s[i]=='1') n = 1; else n = 0;
        dec = dec + (n * pow(2,count));
        count++;
    }
    return dec;
  }

int main(int argc, char** argv){
  char s1[16];//contient le 1er nombre hexadecimal en binaire (penser a rajouter 1 pour le caractere '\0' fin de chaîne)
  char s2[16];//contient le 2eme nombre hexadecimal en binaire (penser a rajouter 1 pour le caractere '\0' fin de chaîne)
  char s3[16];//contient le résultat de l'addition des 2 nombres
  char over_f;//contient '0' si pas d'overflow et contient '1' si overflow


  //Si l'utilisateur inscrit une seule valeur ou 3,4,5,6,etc valeurs
  if (argc != 3){
    printf("Veuillez entrer 2 valeurs a vouloir additionner\n");
    //return 0;
  }
  if (convertir_entree(s1,argv[1])){
    printf("conversion reussi pour valeur 1\n");
    afficher_tab(s1);
  }
  if (convertir_entree(s2,argv[2])){
    printf("conversion reussi pour valeur 2\n");
    afficher_tab(s2);
  }
  over_f = add_16b(s1,s2,s3);
  printf("overflow : %c\n",over_f);

  printf("Le resultat vaut : 0x%x\n",convert(s3));
  afficher_tab(s3);

  return 0;
}
