#include<stdio.h>
#include<malloc.h>
typedef struct Santier Santier; //ne-am definit un alias
typedef struct Nod Nod;

struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct Nod {
    Santier santier;
    Nod* next;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata)
{
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

Nod* inserareInceput(Santier santier, Nod* lista)
{
    Nod* nod=(Nod*)malloc(sizeof(Nod));
    nod->santier = santier;
    nod->next = lista;
    return nod;
}

void afisareSantier(Santier santier)
{
    printf("Santierul %s are %d muncitori si o suprafata de %5.2f mp\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

void afiseazaLista(Nod* lista)
{
    while (lista != NULL)
    {
        //procesare
        afisareSantier(lista->santier);
        lista = lista->next;

    }
}

int nrMuncitori(Nod* lista)
{
    int nr = 0;
    while (lista != NULL)
    {
        nr = nr + lista->santier.nrMuncitori;
        lista = lista->next;
    }
    return nr;
}

void stergeLista(Nod** lista)
{
    while ((*lista) != NULL)
    {
        free((*lista)->santier.numeProiect);
        Nod* aux=(*lista)->next;
        free(*lista);
        (*lista) = aux;
    }
    (*lista) = NULL;
}

float densitate(Santier santier)
{
    if (santier.suprafata != 0)
        return santier.nrMuncitori / santier.suprafata;
    else return 0;
}

//numele santierului cu densitatea cea mai mare de muncitori pe mp
char* santierDensitateMaxima(Nod* lista)
{
    float max = 0;
    char* aux=NULL;
    while (lista != NULL)
    {
        if (densitate(lista->santier) > max) 
        {
            max = densitate(lista->santier);
            aux = lista->santier.numeProiect;
        }
            
        lista = lista->next;
    }
    if (aux != NULL) 
    {
        char* numePrDensMax = (char*)malloc(strlen(aux) + 1);
        strcpy(numePrDensMax, aux);
        return numePrDensMax;
    }
    return NULL;
   
}

//de sters un nod(trb sa facem legatura)

int main() {
    Nod* lista = NULL;
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 2, 200);
    lista = inserareInceput(s1, lista);
    lista = inserareInceput(s2, lista);
    lista = inserareInceput(s3, lista);

    lista = inserareInceput(initializareSantier("Santier 4", 10, 340), lista);

    afiseazaLista(lista);

    int nr = 0;
    nr = nrMuncitori(lista);
    printf("Nr total de muncitori: %d", nr);

    char* numePrDensMax = santierDensitateMaxima(lista);
    printf("\n%s", numePrDensMax);
  
    stergeLista(&lista);
    afiseazaLista(lista);

    return 0;
}