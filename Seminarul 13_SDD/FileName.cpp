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
void inserareMuchie(NodPrincipal* graf,int linieStart, int linieStop)
{
	NodPrincipal* nodStart =cautaLinie(graf,linieStart);
	NodPrincipal* nodStop =cautaLinie(graf,linieStop);
	nodStart->vecini = inserareSecundaraSf(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundaraSf(nodStop->vecini, nodStart);

}

void main()
{
	NodPrincipal* graf=NULL;

	inserareSfarsitPrincipala(&graf, initAutobuz(0, "Romana"));
	inserareSfarsitPrincipala(&graf, initAutobuz(1, "Universitate"));
	inserareSfarsitPrincipala(&graf, initAutobuz(2, "Unirii"));
	inserareSfarsitPrincipala(&graf, initAutobuz(3, "Victoriei"));
	inserareSfarsitPrincipala(&graf, initAutobuz(4, "Militari"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);

}