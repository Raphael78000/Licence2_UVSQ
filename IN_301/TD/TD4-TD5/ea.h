
struct Noeud
{
	int op_ou_val;
	char op;
	float val;
	struct Noeud* sag;
	struct Noeud* sad;
};
typedef struct Noeud* EA;

EA ea_creer_valeur (float val);
EA ea_creer_operation (char op, EA sag, EA sad);
float ea_evaluer (EA e);
void afficher_arbre (EA e);
