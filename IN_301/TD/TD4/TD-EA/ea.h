struct noeud{
	int op_ou_val;
	char op;
	float val;
	struct noeud *opg;
	struct noeud *opd;
};

typedef struct noeud  * EA;

EA ea_creer_valeur (float val);

EA ea_creer_operation (char op, EA opg, EA opd);

float ea_evaluer (EA e);
