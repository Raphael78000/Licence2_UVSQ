//Création d'un système de pile:

//Chaque élèment de la pile aura une structure identique à celle d'ue lite chaînée:

typedef struct Element Element;
struct Element{
    int nombre;
    Element *suivant;
    };

//La structure de contrôle contiendra l'adresse d premier élèment de la pile, celui qi se touve en haut:

typedef struct Pile Pile;
struct Pile{
    Element *premier;
};

//Notre fonction empiler doit prendre en paramètre la structure de contre de la pile ainsi que le nouveau nombre à stocker.

void empiler(Pile *pile, int nvNombre){
    Element *nouveau=malloc(sizeof(*nouveau));
    if (pile==NULL || nouveau==NULL){
        exit(EXIT_FAILURE)
    }
    nouveau->nombre=nvNombre;
    nouveau->suivant=pile->premier;
    pile->premier=nouveau;
}

//Notre fonction depiler va donc retourner un int correspondant au nombre qui se trouvait en tête de pile:

int depiler(Pile *pile){
    if (pile==NULL){
        exit(EXIT_FAILURE);
    }
    int nombreDepile=0;
    Element *elementDepile=pile->premier;
    if (pile!=NULL && pile->premier!=NULL){
        nombreDepile=elementDepile->nombre;
        pile->premier=elementDepile->suivant;
        free(elementDepile);
    }
    return nombreDepile;
}
//Affichage de la pile:

void afficherPile(Pile *pile){
    if(pile==NULL){
        exit(EXIT_FAILURE);
    }
    Element *actuel=pile->premier;
    while (actuel!=NULL){
        printf("%d\n",actuel->nombre);
        actuel=actuel->suivant;
    }
    printf("\n");
}
