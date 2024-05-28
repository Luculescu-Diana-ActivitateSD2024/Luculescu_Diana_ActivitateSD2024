#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
struct Autobuz
{
	int linie; //unica
	char* capatLinie;
};


struct NodPrincipal
{
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};


struct NodSecundar
{
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz initAutobuz(int linie, const char* capat)
{
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy_s(a.capatLinie, strlen(capat) + 1, capat);
	return a;
}

//functie de inserare la sf in lista principala
void inserareSfarsitPrincipala(NodPrincipal** graf, Autobuz a)
{
	NodPrincipal* nodInserat = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nodInserat->info = a;
	nodInserat->next = NULL;
	nodInserat->vecini = NULL;
	if ((*graf) != NULL)
	{
		NodPrincipal* temp = (*graf);
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nodInserat;

	}
	else
	{
		(*graf) = nodInserat;
	}
}

//functie de cautare dupa linie
NodPrincipal* cautaLinie(NodPrincipal* graf, int linie)
{
	while (graf && graf->info.linie != linie)
	{
		graf = graf->next;
	}
	return graf;
}

//functie de inserare in lista secundara
NodSecundar* inserareSecundaraSf(NodSecundar* cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap)
	{
		NodSecundar* p = cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

//functie de inserare muchie
void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop)
{
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareSecundaraSf(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundaraSf(nodStop->vecini, nodStart);

}

int getNrNoduri(NodPrincipal* graf)
{
	int s = 0;
	while (graf)
	{
		s++;
		graf = graf->next;
	}
	return s;
}

#pragma region Coada

typedef struct nodCoada NodCoada;
struct nodCoada
{
	int id;
	NodCoada* next;
};

void inserareCoada(NodCoada** cap, int id)
{
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (*cap)
	{
		NodCoada* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
		*cap = nou;
}

void inserareStiva(NodCoada** cap, int id)
{
	NodCoada* nou= (NodCoada*)malloc(sizeof(NodCoada)); 
	nou->id = id; 
	nou->next = *cap; 
	*cap = nou; 
}

int extrageDinCoada(NodCoada** cap)
{
	if (*cap)
	{
		int rez = (*cap)->id;
		//acum stergem nodul
		NodCoada* temp = (*cap)->next;
		free(*cap);
		*cap = temp;
		return rez;
	}
	else
		return -1;
}

int extrageDinStiva(NodCoada** cap)
{
	return extrageDinCoada(cap);
}

#pragma endregion

void afisareAutobuz(Autobuz a)
{
	printf("%d. are capatul la %s \n\n", a.linie, a.capatLinie);
}

//cand inserez un nod in coada, il pun intr-un vector "de vizitate"
void afisareCuParcurgereInLatime(NodPrincipal* graf, int nodPlecare)
{
	//initializari
	NodCoada* coada = NULL;
	int nrNoduri = getNrNoduri(graf);
	char* vizitate = (char*) malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	inserareCoada(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (coada)
	{
		//extragem nodul din coada
		int idNodCurent = extrageDinCoada(&coada);
		NodPrincipal* nodCurent = cautaLinie(graf, idNodCurent); //cauta vecinii
		afisareAutobuz(nodCurent->info);
		//accesez vecinii
		NodSecundar* temp = nodCurent->vecini;
		//inserare in coada si marcare ca vizitat fiecare vecin
		while (temp)
		{
			if (vizitate[temp->nod->info.linie] == 0)
			{
				vizitate[temp->nod->info.linie] = 1;
				inserareCoada(&coada, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}
	if (vizitate != NULL)
		free(vizitate);
}

void afisareCuParcurgereInAdancime(NodPrincipal* graf, int nodPlecare)
{
	//initializari
	NodCoada* stiva = NULL; 
	int nrNoduri = getNrNoduri(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	inserareStiva(&stiva, nodPlecare); 
	vizitate[nodPlecare] = 1;

	while (stiva)
	{
		//extragem nodul din coada
		int idNodCurent = extrageDinStiva(&stiva);
		NodPrincipal* nodCurent = cautaLinie(graf, idNodCurent); //cauta vecinii
		afisareAutobuz(nodCurent->info);
		//accesez vecinii
		NodSecundar* temp = nodCurent->vecini;
		//inserare in coada si marcare ca vizitat fiecare vecin
		while (temp)
		{
			if (vizitate[temp->nod->info.linie] == 0)
			{
				vizitate[temp->nod->info.linie] = 1;
				inserareStiva(&stiva, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}
	if (vizitate != NULL) 
		free(vizitate); 
}

void stergereListaVecini(NodSecundar** cap)
{
	NodSecundar* p = *cap;
	while (p)
	{
		NodSecundar* aux = p;
		p = p->next;
		free(aux);
	}
	*cap = NULL;
}

//void dezalocareGraf(NodPrincipal** graf)
//{
//	while (*graf)
//	{
//		free((*graf)->info.capatLinie);
//		NodSecundar* p = (*graf)->vecini;
//		while (p)
//		{
//			NodSecundar* aux = p;
//			p = p->next;
//			free(aux);
//		}
//		NodPrincipal* temp = *graf;
//		*graf = temp->next;
//		free(temp);
//	}
//}
void dezalocareGraf(NodPrincipal** graf)
{
	while (*graf)
	{
		free((*graf)->info.capatLinie);
		stergereListaVecini(&((*graf)->vecini));
		NodPrincipal* temp = *graf;
		*graf = temp->next;
		free(temp);
	}
}

void main()
{
	NodPrincipal* graf = NULL;

	inserareSfarsitPrincipala(&graf, initAutobuz(0, "Romana"));
	inserareSfarsitPrincipala(&graf, initAutobuz(1, "Universitate"));
	inserareSfarsitPrincipala(&graf, initAutobuz(2, "Unirii"));
	inserareSfarsitPrincipala(&graf, initAutobuz(3, "Victoriei"));
	inserareSfarsitPrincipala(&graf, initAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 2, 4);
	

	afisareCuParcurgereInLatime(graf, 0);
	printf("\n\n\n");
	afisareCuParcurgereInAdancime(graf, 0);

	dezalocareGraf(&graf);

}