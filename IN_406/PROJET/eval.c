#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define allocate(A) A = malloc(sizeof(struct token));

enum type{
  CONSTANT,
  BINARY_OP,
  UNARY_OP,
  BRACKET,
};
typedef enum type type;

enum op_binary{
  ADD,
  AND,
  INVOLVEMENT,
  EQUIVALENCE,
};
typedef enum op_binary op_binary;

struct token{
  struct token* next;
  type TYPE;
  union{
    bool value;             //if TYPE is a CONSTANT, value is 'true' if '1' else 'false' if '0'
    bool bracket;           //if TYPE is a BRACKET, value is 'true' if '(' else 'false' if ')'
    bool unary;             //if TYPE is a UNARY_OP, value is 'true' if 'NON' else 'false'
    op_binary OpBinary;     //if TYPE is a BINARY_OP, value depends on enum op_binary
  }attribute;
};
typedef struct token* TokenList;

int check(TokenList A){
  if (!A){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    return 1;
  }
}

/*Ajouter un élèment à la liste*/
TokenList add_list(TokenList A,TokenList B){
  TokenList last;

  if (check(A)) return B;

  last = A;
  while (last->next != NULL) last = last->next;
  last->next = B;
  return A;
}

/*Convertir une chaîne de caractère en une liste*/
TokenList string_to_token(char* string){
  TokenList A = NULL;
  TokenList B = NULL;

  while (*string != '\0'){

    if ( (string[0] == '(') || (string[0] == ')') ){
      allocate(A);
      if (check(A)) exit(EXIT_FAILURE);
      A->TYPE = BRACKET;
      if (string[0] == '(') A->attribute.bracket = true;
      else A->attribute.bracket = false;
    }

    else if ( (string[0] == '1') || (string[0] == '0') ){
      allocate(A);
      if (check(A)) exit(EXIT_FAILURE);
      A->TYPE = CONSTANT;
      if (string[0] == '1') A->attribute.value = true;
      else A->attribute.value = false;
    }

    else if ( (string[0] == '+') || (string[0] == '.') ){
      allocate(A);
      if (check(A)) exit(EXIT_FAILURE);
      A->TYPE = UNARY_OP;
      if (string[0] == '+') A->attribute.OpBinary = ADD;
      else A->attribute.OpBinary = AND;
    }

    else if ( (string[0] == 'N') || (string[0] == 'n') ){
          if ( (string[1] == '0') || (string[1] == 'o') ){
            if ( (string[2] == 'N') || (string[2] == 'n') ){
              allocate(A);
              if (check(A)) exit(EXIT_FAILURE);
              A->TYPE = BINARY_OP;
              A->attribute.unary = true;
            }
          }
        }

    else if ( (string[0] == '=') && (string[1] == '>') ){
      allocate(A);
      if (check(A)) exit(EXIT_FAILURE);
      A->TYPE = BINARY_OP;
      A->attribute.OpBinary = INVOLVEMENT;
    }

    else if ( (string[0] == '<') && (string[1] == '=') && (string[2] == '>') ){
      allocate(A);
      if (check(A)) exit(EXIT_FAILURE);
      A->TYPE = BINARY_OP;
      A->attribute.OpBinary = EQUIVALENCE;
    }

    else{
      fprintf(stderr,"Character is not valid\n"); exit(EXIT_FAILURE);
    }
    B = add_list(B,A);
    string++;
  }
  return B;
}

int main(int argc,char ** argv){

  exit(EXIT_SUCCESS);
}
