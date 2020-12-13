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

char* convert_dec_bin(int n,char* tab){
  for (int i = 15; i >= 0; i--){
    if (n % 2) tab[i] = '1';
    else tab[i] = '0';
    n = n / 2;
  }
  return tab;
}

int convertir_entree(char* tab,char* strhexa){
  int dec;
  char* ptr;//contient la chaîne de caractère si elle a été saisie par l'utilisateur(ne prends pas "0x")

  dec = strtol(strhexa,&ptr,16);//va contenir l'héxadécimal au format décimal (base 10)

  if (dec > 65535){
    printf("nombre hexadecimal ne tient pas sur 16 bits\n");
    return 1;
  }
  if (ptr[0] != '\0'){
    printf(" un parametre ne represente pas une valeur hexadecimale\n");
    return 1;
  }
  tab = convert_dec_bin(dec,tab);
  return 0;
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

int convert_bin_dec(char* s){
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
    printf("manque de parametre\n");
    return 1;
  }

  if (convertir_entree(s1,argv[1])==0){
     printf("conversion valeur 1 reussi\n");
     afficher_tab(s1);
   }
   else{
     return 1;
   }
  if (convertir_entree(s2,argv[2])==0){
     printf("conversion valeur 2 reussi\n");
     afficher_tab(s2);
   }
   else{
     return 1;
   }

   over_f = add_16b(s1,s2,s3);

   printf("\nLe resultat est: 0x%x (base 16), ",convert_bin_dec(s3));
   printf("overflow: %c\n",over_f);
   afficher_tab(s3);

  return 0;
}
