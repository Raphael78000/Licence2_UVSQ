//Nou allons créer une strcuture Element et une structure de contre File:

typedef strcut Element Element;
struct Element{
    int nombre;
    Element *suivant;
};

typedef struct File File;
struct File{
    Element *premier;
};

void enfiler(File *file, int nvNombre){
    Element *nouveau=malloc(sizeof(*nouveau));
    if (file==NULL || nouveau==NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->nombre=nvNombre;
    nouveau->suivant=NULL;
    if (file->premier!=NULL){
        Element *elementActuel=file->premier;
        while (elementActuel->suivant!=NULL){
            elementActuel=elementActuel->suivant;
        }
        elementActuel->suivant=nouveau;
    }
    else{
        file->premier=nouveau;
    }
}

int defiler(File *file){
    if (file==NULL){
        exit(EXIT_FALURE);
    }
    int nombreDefile=0;
    if (file->premier!=NULL){
        Element *elementDefile=file->premier;
        nombreDefile=elementDefile->nombre;
        file->premier=elementDefile->sivant;
        free(elementDefile);
    }
    return nombreDefile;
}
