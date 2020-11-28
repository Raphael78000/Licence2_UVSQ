#define PAR_OUV 11
#define PAR_FER 12
#define OP    13
#define VAL   14

struct token {
	int type_token;
	float val;
	char op;
	struct token* prec;
	struct token* suiv;
};
typedef struct token* TOKEN;

TOKEN token_creer(int type, char op, float val);

TOKEN token_ajouter_fin_liste (TOKEN t, TOKEN nouv);

void token_afficher(TOKEN t);

void token_afficher_rec(TOKEN t);

int est_op(char c);

int est_val(char c);

int est_valide(char c);

TOKEN token_creer_val(char **s);

TOKEN token_creer_liste(char *s);
