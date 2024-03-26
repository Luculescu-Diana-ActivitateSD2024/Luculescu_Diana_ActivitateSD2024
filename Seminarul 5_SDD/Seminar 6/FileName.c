#include<stdio.h>
#include<malloc.h>

typedef struct Santier Santier; 
struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

typedef struct NodLdi NodLdi;
struct NodLdi
{
    NodLdi* prev;
    NodLdi* next;
    Santier info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla
{
    NodLdi* prim;
    NodLdi* ultim;
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



void afisareSantier(Santier santier)
{
    printf("Santierul %s are %d muncitori si o suprafata de %5.2f mp\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}




float densitate(Santier santier)
{
    if (santier.suprafata != 0)
        return santier.nrMuncitori / santier.suprafata;
    else return 0;
}

//inserare la inceput
void inserareInceput(ListaDubla* lista, Santier s)
{
    NodLdi* aux = malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;
    if (lista->prim != NULL)
    {
        lista->prim->prev = aux;
        
    }
    else
    {
        lista->ultim = aux;
    }
    lista->prim = aux;
}

void afisareLdiDeLaInceput(ListaDubla lista)
{
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next)
    {
        afisareSantier(nod->info);
    }
    printf("\n\n");
}

//stergerea santierului dupa un nume dat(unic)
void stergereSantierDupaNume(ListaDubla* lista, const char* nume)
{
    NodLdi* nod=lista->prim;
    while (nod != NULL)
    {
        if (strcmp(nod->info.numeProiect, nume) == 0)
        {
            if (nod->prev == NULL) // daca e primul nod
            {
                if (nod->next == NULL)
                {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else
                {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else
            {
                if (nod->next == NULL) // daca e ultimul nod
                {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else // daca suntem la mijloc, facem doar legaturile
                {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }
            free(nod->info.numeProiect);
            free(nod);
            //sau pun aici break in loc de else nod=nod->next;
            nod=NULL;
        }
        else 
            nod = nod->next;
    }
}

void stergereCompleta(ListaDubla* lista)
{
    if (lista != NULL)
    {
        NodLdi* aux = lista->prim;
        while (aux != NULL)
        {
            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

//nr total de muncitori din lista
int nrTotalMuncitori(ListaDubla lista)
{
    int s = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
        s += i->info.nrMuncitori;
    return s;
}

//nr muncitori de pe santierele care au suprafata mai mica decat un parametru dat
int nrMuncitoriSuprafata(ListaDubla lista, float suprafata)
{
    int s = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
    {
        if (i->info.suprafata < suprafata)
            s += i->info.nrMuncitori;
    }
       
    return s;
}

int main() {
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 2, 200);
    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;

    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    afisareLdiDeLaInceput(lista);

  /*  stergereSantierDupaNume(&lista, "Santier 2");
    afisareLdiDeLaInceput(lista);

    stergereSantierDupaNume(&lista, "Santier 1");
    afisareLdiDeLaInceput(lista);

    stergereSantierDupaNume(&lista, "Santier 3");
    afisareLdiDeLaInceput(lista);*/

    int muncitori = nrTotalMuncitori(lista);
    printf("\nNr total de muncitori: %d", muncitori);

    int muncitori2 = nrMuncitoriSuprafata(lista, 350);
    printf("\nNr de muncitori dupa suprafata: %d", muncitori2);

    stergereCompleta(&lista);
    afisareLdiDeLaInceput(lista);

    
    return 0;
}