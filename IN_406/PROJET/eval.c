#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/************************************ data structures ************************************/
enum type{
  CONSTANT,
  BINARY_OP,
  UNARY_OP,
  BRACKET_O,
  BRACKET_C
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
typedef struct token* liste_token;

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
typedef struct noeud* arbre_token;

/************************************ ancillary functions ************************************/

liste_token add_list(liste_token A,liste_token B){
liste_token last;

if (!A) return B;

last = A;
while (A->next != NULL) A = A->next;
A->next = B;
return last;
}

liste_token bracket_token(char c){
liste_token B;
B = malloc(sizeof(struct token));
if (!B){
  fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
  exit(EXIT_FAILURE);
}
if (c == '('){
  B->TYPE = BRACKET_O;
  B->attribute.bracket = true;
}
else{
  B->TYPE = BRACKET_C;
  B->attribute.bracket = false;
}
return B;
}

liste_token constant_token(char c){
liste_token B;
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

liste_token OP_binary_token(char c){
liste_token B;
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

liste_token unary_token(){
liste_token B;
B = malloc(sizeof(struct token));
if (!B){
  fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
  exit(EXIT_FAILURE);
}
B->TYPE = UNARY_OP;
B->attribute.unary = true;
return B;
}

liste_token involvement_token(){
liste_token B;
B = malloc(sizeof(struct token));
if (!B){
  fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
  exit(EXIT_FAILURE);
}
B->TYPE = BINARY_OP;
B->attribute.OpBinary = INVOLVEMENT;
return B;
}

liste_token equivalence_token(){
liste_token B;
B = malloc(sizeof(struct token));
if (!B){
  fprintf(stderr,"[ERR] token allocation in string_to_token function\n");
  exit(EXIT_FAILURE);
}
B->TYPE = BINARY_OP;
B->attribute.OpBinary = EQUIVALENCE;
return B;
}

liste_token infix_to_postfix(liste_token actual){
liste_token A,B,C,D;

A = bracket_token('(');
C = bracket_token('(');
B = A;
while (actual){
  D = actual->next;

  if (actual->TYPE == CONSTANT){
    B->next = actual;
    B = B->next;
  }

  else if (actual->TYPE == BINARY_OP){
    while (C->TYPE == BINARY_OP){
      B->next = C;
      B = B->next;
      C = C->next;
    }
    actual->next = C;
    C = actual;
  }

  else if (actual->TYPE == BRACKET_C){
    while (C->TYPE != BRACKET_O){
      B->next = C;
      B = B->next;
      C = C->next;
    }
    free(actual);
    actual = C->next;
    free(C);
    C = actual;
  }
  else{
    actual->next = C;
    C = actual;
  }
  actual = D;
}

while (C->TYPE != BRACKET_O){
  B->next = C;
  B = B->next;
  C = C->next;
}
free(C);
B->next = NULL;
actual = A;
A = actual->next;
free(actual);
return A;
}

void show_list_token(liste_token A){
liste_token B = A;

  while (B != NULL){
    if (B->TYPE == CONSTANT)  printf("CONSTANT: %d\n",B->attribute.value);
    if (B->TYPE == BINARY_OP) printf("BINARY_OP: %d\n",B->attribute.OpBinary);
    if (B->TYPE == UNARY_OP)  printf("UNARY_OP: %d\n",B->attribute.unary);
    if (B->TYPE == BRACKET_C) printf("BRACKET_C: %d\n",B->attribute.bracket);
    if (B->TYPE == BRACKET_O) printf("BRACKET_O: %d\n",B->attribute.bracket);
    B = B->next;
  }
  printf("\n");
}

arbre_token create_note(liste_token A){
    arbre_token B = malloc(sizeof(struct noeud));

    B->TYPE = A->TYPE;

    if      (B->TYPE == CONSTANT)   B->attribute.value = A->attribute.value;
    else if (B->TYPE == BINARY_OP)  B->attribute.OpBinary = A->attribute.OpBinary;
    else if (B->TYPE == UNARY_OP)   B->attribute.unary = A->attribute.unary;
    else if (B->TYPE == BRACKET_O)  B->attribute.bracket = A->attribute.bracket;
    else if (B->TYPE == BRACKET_C)  B->attribute.bracket = A->attribute.bracket;
    B->sad = B->sag = NULL;
    return B;
  }

void free_tree(arbre_token A){
  arbre_token B = A;

  if (B == NULL) return;

  if (B->sad != NULL) free_tree(B->sad);

  if (B->sag != NULL) free_tree(B->sag);

  free(B);
}

void free_list(liste_token liste){
    liste_token tmp;
    if(liste == NULL) return;
    tmp = liste->next;
    free(liste);
    free_list(tmp);
}

/************************************ project functions ************************************/

liste_token string_to_token(char* string){
liste_token A = NULL;
liste_token B = NULL;

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

arbre_token	create_tree(liste_token A){
  arbre_token B;
  arbre_token* tree = malloc(sizeof(struct noeud));
  int position = 0;

  while (A != NULL){
    B = create_note(A);

    if (A->TYPE == CONSTANT){
      position = position + 1;
    }

    else if (A->TYPE == UNARY_OP){
      B->sag = tree[position - 1];
    }

    else{
      B->sad = tree[position - 1];
      B->sag = tree[--position - 1];
    }
    tree = realloc(tree,sizeof(struct noeud) * position);
    tree[position - 1] = B;
    A = A->next;
  }
  return tree[0];
}

bool tree_evaluation(arbre_token A){
  bool a,b;
  if (A != NULL){

    if (A->TYPE == BINARY_OP){
      bool sag = tree_evaluation(A->sag);
      bool sad = tree_evaluation(A->sad);

      switch (A->attribute.OpBinary){
        case ADD :
          return sag | sad;
          break;
        case AND :
          return sag & sad;
          break;
        case INVOLVEMENT :
          return (!sag) | sad;
          break;
        case EQUIVALENCE :
          a = (!sag) | sad;
          b = (!sad) | sag;
          return a & b;
          break;
      }
    }

    else if (A->TYPE == CONSTANT) return A->attribute.value;

    else if (A->TYPE == UNARY_OP) return (!A->sag);
  }
  fprintf(stderr,"Error tree evaluation\n");
  exit(EXIT_FAILURE);
}

bool recognize_language(liste_token A){
  int count = 0;

	if(!A){
    fprintf(stderr,"liste_token is empty in recognize_language function\n");
    exit(EXIT_FAILURE);
  }

	bool T[2];

  T[0] = true; //T[0] représente l'état q0
  T[1] = false; //T[1] représente l'état q1

	while(A != NULL){

		if (A->TYPE == BRACKET_O || A->TYPE == UNARY_OP){

      if (!T[0]){
        fprintf(stderr,"Language not recognized by automate\n");
        return false;
      }
      else if (A->TYPE == BRACKET_O) count++;
		}

		else if (A->TYPE == BRACKET_C){

      if (!T[1]){
        fprintf(stderr,"Language not recognized by automate\n");
        return false;
      }
      count--;
    }

		else if (A->TYPE == CONSTANT){

      if (!T[0]){
        fprintf(stderr,"Language not recognized by automate\n");
        return false;
      }
      T[1] = true;
      T[0] = false;
    }

    else if (A->TYPE == BINARY_OP){

      if (!T[1]){
        fprintf(stderr,"Language not recognized by automate\n");
        return false;
      }

      if (A->attribute.OpBinary == EQUIVALENCE && !count){
        fprintf(stderr,"Language not recognized by automate\n");
        return false;
      }
      T[0] = true;
      T[1] = false;
    }
    A = A->next;
	}

	if( !T[0] && T[1] && !count ){
    fprintf(stdout,"Language is recognized by automate\n");
    return true;
  }
	else{
    fprintf(stdout,"Language not recognize by automate\n");
    return false;
  }
}

/************************************ main function ************************************/

int main(int argc,char ** argv){
  liste_token A,C;
  arbre_token tree;
  bool result;

  //Question 1
  A = string_to_token(argv[1]);

  //Question 3
  result = recognize_language(A);

  if (result){

    //Question 4
    C = infix_to_postfix(A);
    tree = create_tree(C);
    free_list(C);

    //Question 5
    result = tree_evaluation(tree);
    free_tree(tree);

    printf("\nBoolean expression %s is worth : %d\n\n",argv[1],result);
  }
  else printf("\n");

  exit(EXIT_SUCCESS);
}
