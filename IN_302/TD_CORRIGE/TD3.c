#include <stdio.h>
#include <stdlib.h>

//
#define min(a, b) ((a) < (b)) ? (a) : (b)

//
typedef char          i8;
typedef unsigned char u8;
typedef unsigned int  u32;

//Cette fonction calcule la position du bit le plus a gauche (LMB - Left Most Bit)
//Complexite O(n) avec n le nombre de bits de la valeur passee en parametre (ici, n = 32). 
u8 pos_bit_gauche(u32 v)
{
  u8 p = 0;

  while (v)
    {
      p++;
      v >>= 1;
    }

  return p;
}

//Recherche dichotomique du bit le plus a gauche
//Complexite O(log2(n)). Ici n = 32 = 2^5, donc la complexite est: log2(32) = log2(2^5) = 5.
//Consequemment, il faut 5 iterations pour trouver la position du bit le plus a gauche. 
u8 pos_bit_gauche_dicho(u32 v)
{
  //Position
  u8 p = 0;
  
  //Shifts
  static u32 s[5] = { 16, 8, 4, 2, 1 };

  //Masks
  static u32 m[5] = { 0xFFFF0000, 0xFF00, 0xF0, 0b1100, 0b10 };

  //
  for (u8 i = 0; v && i < 5; i++)
    if (v & m[i]) //Si un bloque positionne a gauche n'est pas nul
      {
	v >>= s[i]; //Decaler la valeur de s[i] bits
	p  += s[i]; //Calculer la position en accumulant les positions decalees
      }

  //Retourne 0 si la valeur de v est nulle
  //Retourne la position a compter de 1, si la valeur de v est non nulle.
  return p + (v != 0);
}

//cette fonction calcule la distance de Hamming du code 2 parmi 5
u32 hamming_2p5()
{
  //
  u32 d  = 0;
  u32 dh = 0xFFFFFFFF;
  
  //Table du codage 2/5
  u8 table[] = {

    0b01100, //0
    0b11000, //1
    0b10100, //2
    0b10010, //3
    0b01010, //4
    0b00110, //5
    0b10001, //6
    0b01001, //7
    0b00101, //8
    0b00011  //9
  };

  //
  for (unsigned i = 0; i < 10; i++)
    for (unsigned j = i + 1; j < 10; j++)
      {
	//Calculer la distance de Hamming entre les deux encodages
	//dh(a, b) = popcount(a xor b)
	//La fonction __builtin_popcount() est fournie par GCC
	d = __builtin_popcount(table[i] ^ table[j]);
	
	//
	printf("dh([%u], [%u]) ==> dh(%02x, %02x) = %u\n", i, j, table[i], table[j], d);

	//Calculer la distance de Hamming minimale
	dh = min(dh, d);
      }
  
  //
  return d;
}

//
int main(int argc, char **argv)
{
  putchar('\n');
  printf("%u\n", pos_bit_gauche(0));
  printf("%u\n", pos_bit_gauche(0x00000001));
  printf("%u\n", pos_bit_gauche(0x00F00001));
  printf("%u\n", pos_bit_gauche(0x80000000));
  
  putchar('\n');
  printf("%d\n", pos_bit_gauche_dicho(0));
  printf("%d\n", pos_bit_gauche_dicho(0x00000001));
  printf("%d\n", pos_bit_gauche_dicho(0x00F00001));
  printf("%d\n", pos_bit_gauche_dicho(0x80000000));  

  //
  printf("\nCode 2 parmi 5:\n");
  printf("La distance de Hamming du code 2 parmi 5: %u\n", hamming_2p5());
  
  return 0;
}
