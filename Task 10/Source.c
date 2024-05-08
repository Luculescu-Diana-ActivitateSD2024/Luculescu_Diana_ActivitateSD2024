#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Rezervare Rezervare;
struct Rezervare
{
	int id;
	char* numeClient;
	int nrPersoane;
};

typedef struct Nod Nod;
struct Nod {
    Rezervare info;
    int prioritate;
    Nod* stanga;
    Nod* dreapta;
};

typedef struct NodLS NodLS;
struct NodLS {
    Rezervare info;
    struct NodLS* urmator;
};

typedef struct NodLD NodLD;
struct NodLD {
    Rezervare info;
    struct NodLD* urmator;
    struct NodLD* anterior;
};

Nod* creareNod(Rezervare rez, int prioritate) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = rez;
    nod->prioritate = prioritate;
    nod->stanga = NULL;
    nod->dreapta = NULL;
    return nod;
}

Nod* rotireDreapta(Nod* nod) {
    Nod* temp = nod->stanga;
    nod->stanga = temp->dreapta;
    temp->dreapta = nod;
    return temp;
}

Nod* rotireStanga(Nod* nod) {
    Nod* temp = nod->dreapta;
    nod->dreapta = temp->stanga;
    temp->stanga = nod;
    return temp;
}

Nod* inserareInAVL(Nod* radacina, Rezervare rez, int prioritate) {
    if (radacina == NULL)
        return creareNod(rez, prioritate);

    if (prioritate < radacina->prioritate)
        radacina->stanga = inserareInAVL(radacina->stanga, rez, prioritate);
    else
        radacina->dreapta = inserareInAVL(radacina->dreapta, rez, prioritate);

    if (radacina->stanga != NULL && radacina->stanga->prioritate > radacina->prioritate)
        radacina = rotireDreapta(radacina);
    else if (radacina->dreapta != NULL && radacina->dreapta->prioritate > radacina->prioritate)
        radacina = rotireStanga(radacina);

    return radacina;
}

Rezervare cautareNodDupaID(Nod* radacina, int id) {
    if (radacina)
    {
        if (id < radacina->info.id)
            return cautareNodDupaID(radacina->stanga, id);
        else
            if (id > radacina->info.id)
                return cautareNodDupaID(radacina->dreapta, id);
            else
                return radacina->info;
    }
    else
    {
        Rezervare r;
        r.id = -1;
        r.numeClient = NULL;
        r.nrPersoane = -1;
        return r;
    }
    
}

void salvarePreordineVector(Nod* radacina, Nod** vector, int* index) {
    if (radacina != NULL) {
        vector[(*index)++] = radacina;
        salvarePreordineVector(radacina->stanga, vector, index);
        salvarePreordineVector(radacina->dreapta, vector, index);
    }
}

void salvareInordineVector(Nod* radacina, Nod** vector, int* index) {
    if (radacina != NULL) {
        salvareInordineVector(radacina->stanga, vector, index);
        vector[(*index)++] = radacina;
        salvareInordineVector(radacina->dreapta, vector, index);
    }
}

void salvarePostordineVector(Nod* radacina, Nod** vector, int* index) {
    if (radacina != NULL) {
        salvarePostordineVector(radacina->stanga, vector, index);
        salvarePostordineVector(radacina->dreapta, vector, index);
        vector[(*index)++] = radacina;
    }
}

//lista simpla
NodLS* creareNodLS(Rezervare rez) {
    NodLS* nod = (NodLS*)malloc(sizeof(NodLS));
    nod->info = rez;
    nod->urmator = NULL;
    return nod;
}
void adaugaNodLaSfarsitLS(NodLS** cap, Rezervare rez) {
    NodLS* nodNou = creareNodLS(rez);
    if (*cap == NULL) {
        *cap = nodNou;
    }
    else {
        NodLS* curent = *cap;
        while (curent->urmator != NULL) {
            curent = curent->urmator;
        }
        curent->urmator = nodNou;
    }
}

void salvarePreordineLS(Nod* radacina, NodLS** lista) {
    if (radacina != NULL) {
        adaugaNodLaSfarsitLS(lista, radacina->info);
        salvarePreordineLS(radacina->stanga, lista);
        salvarePreordineLS(radacina->dreapta, lista);
    }
}

void salvareInordineLS(Nod* radacina, NodLS** lista) {
    if (radacina != NULL) {
        salvareInordineLS(radacina->stanga, lista);
        adaugaNodLaSfarsitLS(lista, radacina->info);
        salvareInordineLS(radacina->dreapta, lista);
    }
}

void salvarePostordineLS(Nod* radacina, NodLS** lista) {
    if (radacina != NULL) {
        salvarePostordineLS(radacina->stanga, lista);
        salvarePostordineLS(radacina->dreapta, lista);
        adaugaNodLaSfarsitLS(lista, radacina->info);
    }
}

void afisareLS(NodLS* cap) {
    NodLS* curent = cap;
    while (curent != NULL) {
        printf("%d ", curent->info.id);
        curent = curent->urmator;
    }
}

//lista dubla
NodLD* creareNodLD(Rezervare rez) {
    NodLD* nod = (NodLD*)malloc(sizeof(NodLD));
    nod->info = rez;
    nod->urmator = NULL;
    nod->anterior = NULL;
    return nod;
}

void adaugaNodLaSfarsitLD(NodLD** cap, Rezervare rez) {
    NodLD* nodNou = creareNodLD(rez);
    if (*cap == NULL) {
        *cap = nodNou;
    }
    else {
        NodLD* curent = *cap;
        while (curent->urmator != NULL) {
            curent = curent->urmator;
        }
        curent->urmator = nodNou;
        nodNou->anterior = curent;
    }
}

void salvarePreordineLD(Nod* radacina, NodLD** lista) {
    if (radacina != NULL) {
        adaugaNodLaSfarsitLD(lista, radacina->info);
        salvarePreordineLD(radacina->stanga, lista);
        salvarePreordineLD(radacina->dreapta, lista);
    }
}

void salvareInordineLD(Nod* radacina, NodLD** lista) {
    if (radacina != NULL) {
        salvareInordineLD(radacina->stanga, lista);
        adaugaNodLaSfarsitLD(lista, radacina->info);
        salvareInordineLD(radacina->dreapta, lista);
    }
}

void salvarePostordineLD(Nod* radacina, NodLD** lista) {
    if (radacina != NULL) {
        salvarePostordineLD(radacina->stanga, lista);
        salvarePostordineLD(radacina->dreapta, lista);
        adaugaNodLaSfarsitLD(lista, radacina->info);
    }
}

void afisareListaDubla(NodLD* cap) {
    NodLD* curent = cap;
    while (curent != NULL) {
        printf("%d ", curent->info.id);
        curent = curent->urmator;
    }
}


void main()
{
    Nod* radacina = NULL;

    radacina = inserareInAVL(radacina, (Rezervare) { 5, "Diana", 2 }, 5);
    radacina = inserareInAVL(radacina, (Rezervare) { 3, "Ioana", 3 }, 3);
    radacina = inserareInAVL(radacina, (Rezervare) { 7, "Radu", 4 }, 7);

    int idCautat = 3;
    Rezervare rezultatCautare = cautareNodDupaID(radacina, idCautat);
    if (rezultatCautare.id != -1)
        printf("Rezervarea cu ID-ul %d a fost gasita\n", idCautat);
    else
        printf("Rezervarea cu ID-ul %d nu a fost gasita\n", idCautat);

    int dimensiuneArbore = 3; 
    Nod** vectorPreordine = (Nod**)malloc(dimensiuneArbore * sizeof(Nod*));
    Nod** vectorInordine = (Nod**)malloc(dimensiuneArbore * sizeof(Nod*));
    Nod** vectorPostordine = (Nod**)malloc(dimensiuneArbore * sizeof(Nod*));

    int index = 0;
    salvarePreordineVector(radacina, vectorPreordine, &index);

    index = 0;
    salvareInordineVector(radacina, vectorInordine, &index);

    index = 0;
    salvarePostordineVector(radacina, vectorPostordine, &index);

    printf("\nPreordine vector: ");
    for (int i = 0; i < dimensiuneArbore; i++) {
        printf("%d ", vectorPreordine[i]->info.id);
    }

    printf("\nInordine vector: ");
    for (int i = 0; i < dimensiuneArbore; i++) {
        printf("%d ", vectorInordine[i]->info.id);
    }

    printf("\nPostordine vector: ");
    for (int i = 0; i < dimensiuneArbore; i++) {
        printf("%d ", vectorPostordine[i]->info.id);
    }
    printf("\n\n");

    NodLS* lsPreordine = NULL;
    salvarePreordineLS(radacina, &lsPreordine);
    printf("\nLista simpla preordine: ");
    afisareLS(lsPreordine);

    NodLS* lsInordine = NULL;
    salvareInordineLS(radacina, &lsInordine);
    printf("\nLista simpla inordine: ");
    afisareLS(lsInordine);

    NodLS* lsPostordine = NULL;
    salvarePostordineLS(radacina, &lsPostordine);
    printf("\nLista simpla postordine: ");
    afisareLS(lsPostordine);
    printf("\n\n");

    NodLD* ldPreordine = NULL;
    salvarePreordineLD(radacina, &ldPreordine);
    printf("\nLista dubla preordine: ");
    afisareListaDubla(ldPreordine);

    NodLD* ldInordine = NULL;
    salvareInordineLD(radacina, &ldInordine);
    printf("\nLista dubla inordine: ");
    afisareListaDubla(ldInordine);

    NodLD* ldPostordine = NULL;
    salvarePostordineLD(radacina, &ldPostordine); 
    printf("\nLista dubla postordine: ");
    afisareListaDubla(ldPostordine);

}