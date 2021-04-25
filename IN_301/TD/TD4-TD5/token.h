#define PAR_O 11
#define PAR_F 12
#define OP    13
#define VAL   14

struct token {
	int type_token; // prend une des 4 valeurs :
					// PAR_O, PAR_F, OP, VAL
	char op;
	float val;
	struct token *suiv;
	struct token *prec;
};

typedef struct token * TOKEN;


TOKEN token_ajouter_fin_liste (TOKEN t, TOKEN e);
TOKEN token_creer_liste (char *s);
void token_afficher (TOKEN t);
