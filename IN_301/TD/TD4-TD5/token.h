
struct token {
	int type_token;
	float val;
	char op;
	struct token* prec;
	struct token* suiv;
};
typedef struct token* TOKEN;

TOKEN token_creer_val (float val);
TOKEN token_creer_op ( char op );
TOKEN token_ajouter_fin_liste (TOKEN t, TOKEN T);
TOKEN token_creer_liste (char* s);
EA token_to_ea (TOKEN t);
void token_afficher(TOKEN t);
