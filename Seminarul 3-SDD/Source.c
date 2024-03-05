#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++)
	{
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m;
	(*nrMasini)++;
	if (masini != NULL)
		free(masini);
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini)
{
	FILE* f = fopen(numeFisier, "r");
	//fgets- fct care citeste o linie intreaga
	char buffer[100];
	char delimitator[] = ",\n";
	struct Masina* masini = NULL;
	(*nrMasini) = 0;
	//cat timp returneaza ceva != NULL =>a citit o linie
	while (fgets(buffer, 100, f) != NULL) {
		char* token = strtok(buffer, delimitator); //sau strtok(buffer,",\n");
		struct Masina m;
		m.id = atoi(token); //ascii to int
		token = strtok(NULL, delimitator); //obtinem producatorul
		m.producator = malloc(strlen(token) + 1);
		strcpy(m.producator, token);
		token = strtok(NULL, delimitator);
		m.nrUsi = atoi(token);
		token = strtok(NULL, delimitator);
		m.pret = atof(token);//ascii to float

		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(f);
	return masini;
}

//struct Masina* masiniMulteUsi(struct Masina* masini, int nrMasini)
//{
//	int nrMasiniMulteUsi = 0;
//	for (int i = 0; i < nrMasini; i++)
//	{
//		if (masini[i].nrUsi > 2) nrMasiniMulteUsi++;
//	}
//	struct Masina* masiniMulteUsi = (struct Masina*)malloc(sizeof(struct Masina) * nrMasiniMulteUsi);
//	int j = 0;
//	for (int i = 0; i < nrMasiniMulteUsi; i++)
//	{
//		if (masini[i].nrUsi > 2)
//		{
//			masiniMulteUsi[j] = masini[i];
//			j++;
//		}
//	}
//	return masiniMulteUsi;
//}

int main()
{
	int nrMasini = 0;
	struct Masina* masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		printf("Masina %d:\n", i + 1);
		printf("ID: %d\n", masini[i].id);
		printf("Producator: %s\n", masini[i].producator);
		printf("Nr. usi: %d\n", masini[i].nrUsi);
		printf("Pret: %5.2f\n\n\n", masini[i].pret);
	}

	printf("\n\n--------------\n\n");

	return 0;
}