struct token{
	int type_token;
	char op;
	float val;
	struct token *prec;
	struct token *suiv;
};
typedef struct token *TOKEN;

TOKEN token_creer_liste(char *s);

EA token_to_ea(TOKEN t);
