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
struct Nod
{
	Nod* dreapta;
	Nod* stanga;
	Rezervare info;
};

Rezervare citireRezervareFisier(FILE* f)
{
	Rezervare r;
	char aux[30];
	fscanf(f, "%d", &r.id);
	fscanf(f, "%s", &aux);
	r.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &r.nrPersoane);
	return r;
}


Nod* rotireLaDreapta(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->stanga;
		rad->stanga = aux->dreapta;
		aux->dreapta = rad;
		return aux;
	}
	return NULL;
}

Nod* rotireLaStanga(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->dreapta;
		rad->dreapta = aux->stanga;
		aux->stanga = rad;
		return aux;
	}
	return NULL;
}

//inserarea se face mereu pe un nod frunza
Nod* inserareInArbore(Nod* arbore, Rezervare rez)
{
	if (arbore != NULL)
	{
		if (arbore->info.id < rez.id)
		{
			arbore->dreapta = inserareInArbore(arbore->dreapta, rez);
		}
		else
		{
			arbore->stanga = inserareInArbore(arbore->stanga, rez);
		}
		int grad = calculGradEchilibru(arbore);
		if (grad == 2)
		{
			//dezechilibru in stanga
			/*if (calculGradEchilibru(arbore->stanga)==1)
			{
				arbore = rotireLaDreapta(arbore); 
			}
			else
			{
				arbore->stanga = rotireLaStanga(arbore->stanga);
				arbore = rotireLaDreapta(arbore);
			}*/
			if (calculGradEchilibru(arbore->stanga) == -1)
			{
				arbore->stanga = rotireLaStanga(arbore->stanga); 
			}
			arbore = rotireLaDreapta(arbore); 
		}

		if (grad == -2)
		{
			//dez in dreapta
			if (calculGradEchilibru(arbore->dreapta) == 1)
			{
				arbore->dreapta = rotireLaDreapta(arbore->dreapta);
				
			}
			arbore = rotireLaStanga(arbore); 
		}
	}
	else
	{
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez;//shallow copy
		temp->dreapta = NULL;
		temp->stanga = NULL;

		arbore = temp;
	}

	return arbore;
}

//citim datele din fisier si returnam arborele binar de cautare
void citireFisier(const char* numef, Nod** radacina)
{
	FILE* f = fopen(numef, "r");
	int nr;
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		Rezervare r;
		r = citireRezervareFisier(f);
		*radacina = inserareInArbore(*radacina, r);
	}
}

void afisareRezervare(Rezervare r)
{
	printf("Rezervarea cu ID-ul %d a fost facuta de %s pentru %d persoane\n\n", r.id, r.numeClient, r.nrPersoane);
}

//afisare:
//RSD-preordine
//SDR-postordine
//SRD-inordine sau binara
void afisareArborePREORDINE(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareRezervare(arbore->info);
		afisareArborePREORDINE(arbore->stanga);
		afisareArborePREORDINE(arbore->dreapta);
	}
}

void afisareArboreINORDINE(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareArboreINORDINE(arbore->stanga);
		afisareRezervare(arbore->info);
		afisareArboreINORDINE(arbore->dreapta);
	}
}

void afisareArborePOSTORDINE(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareArborePOSTORDINE(arbore->stanga);
		afisareArborePOSTORDINE(arbore->dreapta);
		afisareRezervare(arbore->info);
	}
}

Rezervare cautaRezDupaID(Nod* rad, int id)
{
	if (rad != NULL)
	{
		if (rad->info.id < id)
		{
			return cautaRezDupaID(rad->dreapta, id);
		}
		else
		{
			if (rad->info.id > id)
			{
				return cautaRezDupaID(rad->stanga, id);
			}
			else
			{
				return rad->info;
			}
		}
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

int calculNrTotalPersoane(Nod* radacina)
{
	if (radacina)
	{
		int rPersoane = radacina->info.nrPersoane;
		int sPersoane = calculNrTotalPersoane(radacina->stanga);
		int dPersoane = calculNrTotalPersoane(radacina->dreapta);
		int suma = rPersoane + sPersoane + dPersoane;
		return suma;
	}
	else
		return 0;
}
 //grad de echilibru=inaltime stanga-inaltime dreapta(sau invers)


int inaltimeArbore(Nod* rad)
{
	if (rad)
	{
		int inaltimeStanga = inaltimeArbore(rad->stanga);
		int inaltimeDreapta = inaltimeArbore(rad->dreapta);
		/*int maxim;
		if (inaltimeStanga > inaltimeDreapta)
			maxim = inaltimeStanga;
		else
			maxim = inaltimeDreapta;
		maxim = maxim + 1;*/
		return 1 + (inaltimeStanga > inaltimeDreapta ? inaltimeStanga : inaltimeDreapta);
	}
	
	return 0;
}

int calculGradEchilibru(Nod* rad)
{
	if (rad)
	{
		int inaltimeStanga = inaltimeArbore(rad->stanga); 
		int inaltimeDreapta = inaltimeArbore(rad->dreapta);
		return inaltimeStanga - inaltimeDreapta; 
	}
	return 0;
}

//stergerea intregului arbore
//cand sterg un nod, trebuie sa verific mereu gr de ech
void stergereArbore(Nod** rad)
{
	if ((*rad))
	{
		//folosesc postordine pt a sterge mai intai fiii
		stergereArbore(&(*rad)->stanga);
		stergereArbore(&(*rad)->dreapta);
		free((*rad)->info.numeClient);
		free(*rad);
		(*rad) = NULL;
	}
}

void main()
{
	Nod* radacina = NULL;
	citireFisier("rezervari.txt", &radacina);
	afisareArborePREORDINE(radacina);
	//afisareArboreINORDINE(radacina);
	//afisareArborePOSTORDINE(radacina);

	printf("Cautare id\n");
	afisareRezervare(cautaRezDupaID(radacina, 8));

	printf("\nNr. total de persoane: %d", calculNrTotalPersoane(radacina));

	stergereArbore(&radacina);
	afisareArborePREORDINE(radacina); 

}