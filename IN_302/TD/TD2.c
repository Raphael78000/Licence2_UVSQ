/*
  Compilation:

    $ gcc codes_td2.c -o code_td2

    or

    $ clang codes_td2.c -o code_td2

  Execution:

    $ ./codes_td2 100

    affiche_parite v1:
    4: Pair / even
    5: Impair / odd
    --------------------------------------

    affiche_parite_v2:
    4: Pair / even
    5: Impair / odd
    --------------------------------------

    verifie_premier_dernier:
    164: 0
    35: 1
    110: 0
    --------------------------------------

    get_size_v1:
    100: 3
    --------------------------------------

    get_size_v2:
    100: 3
    --------------------------------------

    get_size_v3: (Voodo)
    100: 3


    $./codes_td2 ENTER_ANY_NUMBER

*/

//
#include <stdio.h>
#include <stdlib.h>

//
#define __newline__ puts("--------------------------------------\n")

//
typedef unsigned char      bool; //8 bits unsigned used for boolean values
typedef unsigned char      u8;   //8 bits unsigned
typedef unsigned short     u16;  //16 bits unsigned
typedef unsigned int       u32;  //32 bits unsigned
typedef unsigned long long u64;  //64 bits unsigned

//
void affiche_parite_v1(u32 n)
{
  //
  if (n & 1)
    printf("%u: Impair / odd\n", n);
  else
    printf("%u: Pair / even\n", n);
}

//
void affiche_parite_v2(u32 n)
{
  //
  const char *choix[] = { "Pair / even", "Impair / odd" };

  //
  printf("%u: %s\n", n, choix[n & 1]);
}

//Return true (1) if the most significant, or the least significant, bit is set
//Retourne 1 si le bit de poids faible ou le bit de poids fort est a 1.
bool verifie_premier_dernier(u32 n)
{
  //n >> 31 moves the MSB in to the LSB position.
  //n & 1 keeps the LSB only
  //Smash them together with an or and you get the answer

  //a = n >> 31, place le bit de poids ford a la position de poids faible
  //b = n & 1 conserve le bit de poids faible
  //Si a ou b est a 1, le resultat est 1
  return ((n >> 31) | (n & 1));
}

//
#define NB_BITS 32

//Naive version (Complexity: O(m) with m the number of bits, in this case 32)
u8 get_size_v1(u32 n)
{
  //Counter
  u8 c = 0;

  //
  for (u8 i = 0; i < NB_BITS; i++)
    {
      //Check if n & 1 == 1
      if (n & 1)
	c++; //Count

      //Move to next bit
      n = n >> 1;
    }

  //
  return c;
}

//Better best case complexity than the naive version but still O(m) with m the number of bits.
u8 get_size_v2(u32 n)
{
  //Counter
  u8 c = 0;

  //
  while (n)
    {
      //n & 1 is either = 0 or = 1
      //when = 1 the accumulation counts the number of bits set to 1
      c += (n & 1);

      //Move to next bit
      n >>= 1;
    }

  //
  return c;
}

//Some Voodo magic!
u8 get_size_v3(u32 n)
{
  if (n)
    return get_size_v3(n >> 1) + (n & 1);
}

//
int main(int argc, char **argv)
{
  //Check parameters
  if (argc < 2)
    return printf("Usage: %s [n]\n", argv[0]), 1;

  //Get parameter and convert from string to u32
  u32 n = (u32)atol(argv[1]);

  //
  puts("affiche_parite v1:");

  affiche_parite_v1(4);
  affiche_parite_v1(5);

  __newline__;

  //
  puts("affiche_parite_v2:");

  affiche_parite_v2(4);
  affiche_parite_v2(5);

  __newline__;

  //
  puts("verifie_premier_dernier:");

  printf("164: %u\n", verifie_premier_dernier(164));
  printf(" 35: %u\n", verifie_premier_dernier(35));
  printf("110: %u\n", verifie_premier_dernier(110));

  __newline__;

  //
  puts("get_size_v1:");

  printf("%u: %u\n", n, get_size_v1(n));

  __newline__;

  //
  puts("get_size_v2:");

  printf("%u: %u\n", n, get_size_v2(n));

  __newline__;

  //
  puts("get_size_v3: (Voodo)");

  printf("%u: %u\n", n, get_size_v3(n));

  //
  return 0;
}
