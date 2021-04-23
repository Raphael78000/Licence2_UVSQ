#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define EXPRESSION "NON"

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
  struct token* prev;
  type TYPE;
  union{
    bool value;             //if TYPE is a CONSTANT, value is 'true' if '1' else 'false' if '0'
    bool bracket;           //if TYPE is a BRACKET, value is 'true' if '(' else 'false' if ')'
    bool unary;             //if TYPE is a UNARY_OP, value is 'true' if 'NON' else 'false'
    op_binary OpBinary;     //if TYPE is a BINARY_OP, value depends on enum op_binary
  }attribute;
};
typedef struct token* TokenList;

struct noeud{
  struct noeud* sag;
  struct noeud* sad;
  type TYPE;
  union{
    bool value;             //if TYPE is a CONSTANT, value is 'true' if '1' else 'false' if '0'
    bool bracket;           //if TYPE is a BRACKET, value is 'true' if '(' else 'false' if ')'
    bool unary;             //if TYPE is a UNARY_OP, value is 'true' if 'NON' else 'false'
    op_binary OpBinary;     //if TYPE is a BINARY_OP, value depends on enum op_binary
  }attribute;
};
typedef struct noeud* noeud;

  /************************************ Fonctions TokenList ************************************/

TokenList add_list(TokenList A,TokenList B){
  TokenList last;

  if (!A) return B;

  last = A;
  while (A->next != NULL) A = A->next;
  A->next = B;
  B->prev = A;
  return last;
}

TokenList bracket_token(char c){
  TokenList B;
  B = malloc(sizeof(struct token));
  if (!B){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    exit(EXIT_FAILURE);
  }
  B->TYPE = BRACKET;
  if (c == '(') B->attribute.bracket = true;
  else B->attribute.bracket = false;
  return B;
}

TokenList constant_token(char c){
  TokenList B;
  B = malloc(sizeof(struct token));
  if (!B){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    exit(EXIT_FAILURE);
  }
  B->TYPE = CONSTANT;
  if (c == '1') B->attribute.value = true;
  else B->attribute.value = false;
  return B;
}

TokenList OP_binary_token(char c){
  TokenList B;
  B = malloc(sizeof(struct token));
  if (!B){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    exit(EXIT_FAILURE);
  }
  B->TYPE = BINARY_OP;
  if (c == '+') B->attribute.OpBinary = ADD;
  else B->attribute.OpBinary = AND;
  return B;
}

TokenList unary_token(){
  TokenList B;
  B = malloc(sizeof(struct token));
  if (!B){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    exit(EXIT_FAILURE);
  }
  B->TYPE = UNARY_OP;
  B->attribute.unary = true;
  return B;
}

TokenList involvement_token(){
  TokenList B;
  B = malloc(sizeof(struct token));
  if (!B){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    exit(EXIT_FAILURE);
  }
  B->TYPE = BINARY_OP;
  B->attribute.OpBinary = INVOLVEMENT;
  return B;
}

TokenList equivalence_token(){
  TokenList B;
  B = malloc(sizeof(struct token));
  if (!B){
    fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
    exit(EXIT_FAILURE);
  }
  B->TYPE = BINARY_OP;
  B->attribute.OpBinary = EQUIVALENCE;
  return B;
}

TokenList string_to_token(char* string){
  TokenList A = NULL;
  TokenList B = NULL;

  while (*string != '\0'){

    if ( (string[0] == '(') || (string[0] == ')') ) A = bracket_token(string[0]);
    else{
      if ( (string[0] == '1') || (string[0] == '0') ) A = constant_token(string[0]);
      else{
        if ( (string[0] == '+') || (string[0] == '.') ) A = OP_binary_token(string[0]);
        else{
          if ((string[0] == 'N') && (string[1] == 'O') && (string[2] == 'N') ){
            A = unary_token();
            string++;string++;
          }
          else{
            if ( (string[0] == '=') && (string[1] == '>') ){
              A = involvement_token();
              string++;
            }
            else{
              if ( (string[0] == '<') && (string[1] == '=') && (string[2] == '>') ){
                A = equivalence_token();
                string++;string++;
              }
              else{
                fprintf(stderr,"Character is not valid\n");
                exit(EXIT_FAILURE);
              }
            }
          }
        }
      }
    }
    B = add_list(B,A);
    string++;
  }
  return B;
}

TokenList undo_brackets(TokenList A){
  TokenList B = A;
  if (!B){
    fprintf(stderr,"[ERR] C TokenList is empty in undo_brackets function\n");
    exit(EXIT_FAILURE);
  }

  while (B->next != NULL) B = B->next;

  if ( (A->TYPE == BRACKET) && (B->TYPE == BRACKET) ){
    TokenList C;
    C = A;
    if (!C){
      fprintf(stderr,"[ERR] C TokenList is empty in undo_brackets function\n");
      exit(EXIT_FAILURE);
    }

    A = A->next;
    A->prev = NULL;
    free(C);

    C = B;
    if (!C){
      fprintf(stderr,"[ERR] C TokenList is empty in undo_brackets function\n");
      exit(EXIT_FAILURE);
    }

    B = B->prev;
    B->next = NULL;
    free(C);
  }
  return A;
}

TokenList find_BINARY_OP(TokenList A){

  while ( A && (A->TYPE != BINARY_OP) ) A = A->next;
  return A;
}

TokenList token_for_sag(TokenList A,TokenList B){
  B->prev->next = NULL;
  B->prev = NULL;
  return A;
}

TokenList token_for_sad(TokenList A,TokenList B){
  A = B->next;
  A->prev = NULL;
  B->next = NULL;
  return A;
}

void show_list_token(TokenList A){
	TokenList B;

	B = A;

	while (B != NULL){
		if (B->TYPE == CONSTANT) printf("CONSTANT: %d\n",B->attribute.value);
		if (B->TYPE == BINARY_OP) printf("BINARY_OP: %d\n",B->attribute.OpBinary);
    if (B->TYPE == UNARY_OP) printf("UNARY_OP: %d\n",B->attribute.unary);
    if (B->TYPE == BRACKET) printf("BRACKET: %d\n",B->attribute.bracket);
		B = B->next;
	}
	printf("\n");
}

  /************************************ Fonctions noeud ************************************/

noeud transform_token_in_noeud(TokenList A){
  noeud B = malloc(sizeof(struct noeud));

  B->TYPE = A->TYPE;

  if (A->TYPE == CONSTANT) B->attribute.value = A->attribute.value;

  else{
    if (A->TYPE == BINARY_OP) B->attribute.OpBinary = A->attribute.OpBinary;

    else{
      if (A->TYPE == UNARY_OP) B->attribute.unary = A->attribute.unary;
    }
  }
  B->sag = B->sad = NULL;
  free(A);
  return B;
}

noeud transform_token_note(TokenList A){
  noeud B = malloc(sizeof(struct noeud));

  B->TYPE = A->TYPE;

  if      (B->TYPE == CONSTANT)   B->attribute.value = A->attribute.value;
  else if (B->TYPE == BINARY_OP)  B->attribute.OpBinary = A->attribute.OpBinary;
  else if (B->TYPE == UNARY_OP)   B->attribute.unary = A->attribute.unary;
  else if (B->TYPE == BRACKET)    B->attribute.bracket = A->attribute.bracket;
  B->sag = B->sad = NULL;
  free(A);
  return B;
}

noeud Token_to_Note(TokenList A){
  noeud B;
  if (!A->next) return transform_token_note(A);
/*
  TokenList C;
  do{
    C = A;
    if (!C){
      fprintf(stderr,"[ERR] C TokenList is empty in undo_brackets function\n");
      exit(EXIT_FAILURE);
    }
    A = undo_brackets(C);

  }while (C != A);
  */
  TokenList OP = find_BINARY_OP(A);
  TokenList G,D;
  G = token_for_sag(A,OP);
  D = token_for_sad(A,OP);

  B = transform_token_note(OP);
  B->sag = Token_to_Note(G);
  B->sad = Token_to_Note(D);
  return B;
}

int main(int argc,char ** argv){
  TokenList A;
  noeud B;

  A = string_to_token(EXPRESSION);
  show_list_token(A);

  B = Token_to_Note(A);

  exit(EXIT_SUCCESS);
}
