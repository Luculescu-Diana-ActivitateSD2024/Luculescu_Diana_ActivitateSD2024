#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Duplex
{
	int codPostal;
	char* locatie;
	int nrEtaje;
	float* suprafeteEtaje;
};

Duplex citire()
{
	struct Duplex d;

	printf("\nIntroduceti codul postal al duplexului: "); scanf("%d", &d.codPostal);
	printf("\nIntroduceti localitatea in care se afla duplexul: ");
	getchar();
	d.locatie = (char*)malloc(100 * sizeof(char));
	fgets(d.locatie, 100, stdin);
	printf("\nIntroduceti nr de etaje: "); scanf("%d", &d.nrEtaje);
	if (d.nrEtaje > 0)
	{
		d.suprafeteEtaje = (float*)malloc(d.nrEtaje * sizeof(float));
		for (int i = 0; i < d.nrEtaje; i++)
		{
			printf("\nIntroduceti suprafata etajului %d: ", i + 1);
			scanf("%f", &d.suprafeteEtaje[i]);
		}
	}
	return d;
}

float suprafataTotala(struct Duplex d) {
	float suprafataTotala = 0;
	for (int i = 0; i < d.nrEtaje; i++) {
		suprafataTotala += d.suprafeteEtaje[i];
	}
	return suprafataTotala;
}

void modificareCodPostal(Duplex& d, int newCodPostal) {
	d.codPostal = newCodPostal;
}

void afisareDuplex(struct Duplex d)
{
	printf("\nCod postal: %d", d.codPostal);
	if (d.locatie != NULL) printf("\nLocatie: %s", d.locatie);
	printf("\nNr etaje: %d", d.nrEtaje);
	if (d.suprafeteEtaje != NULL)
	{
		printf("\nSuprafetele etajelor:");
		for (int i = 0; i < d.nrEtaje; i++)
			printf("\netajul %d: %5.2f mp", i + 1, d.suprafeteEtaje[i]);
	}
	printf("\n");
}

struct Duplex* vectorMinim2Etaje(struct Duplex* vectorDuplex, int dim)
{
	int nr = 0;
	for (int i = 0; i < dim; i++)
		if (vectorDuplex[i].nrEtaje >= 2) nr++;
	struct Duplex* vectorNou = (struct Duplex*)malloc(nr * sizeof(struct Duplex));
	nr = 0;
	for (int i = 0; i < dim; i++)
		if (vectorDuplex[i].nrEtaje >= 2)
		{
			vectorNou[nr].codPostal = vectorDuplex[i].codPostal;
			vectorNou[nr].locatie = (char*)malloc(100 * sizeof(char));
			strcpy(vectorNou[nr].locatie, vectorDuplex[i].locatie);
			vectorNou[nr].nrEtaje = vectorDuplex[i].nrEtaje;
			vectorNou[nr].suprafeteEtaje = (float*)malloc(vectorNou[nr].nrEtaje * sizeof(float));
			for (int j = 0; j < vectorNou[nr].nrEtaje; j++)
				vectorNou[nr].suprafeteEtaje[j] = vectorDuplex[i].suprafeteEtaje[j];
			afisareDuplex(vectorNou[nr]);
			nr++;
		}
	return vectorNou;
}

struct Duplex copiereDuplex(struct Duplex d)
{
	struct Duplex duplexNou;
	duplexNou.codPostal = d.codPostal;
	duplexNou.locatie = (char*)malloc(100 * sizeof(char));
	strcpy(duplexNou.locatie, d.locatie);
	duplexNou.nrEtaje = d.nrEtaje;
	for (int i = 0; i < d.nrEtaje; i++)
		duplexNou.suprafeteEtaje[i] = d.suprafeteEtaje[i];
	return duplexNou;
}

void mutareDuplex(struct Duplex* d, int dim)
{
	int nr = 0, j = 0, k = 0;
	for (int i = 0; i < dim; i++)
	{
		if (suprafataTotala(d[i]) >= 300) nr++;
	}
	struct Duplex* verifica = (struct Duplex*)malloc(nr * sizeof(struct Duplex));
	struct Duplex* nuVerifica = (struct Duplex*)malloc((dim - nr) * sizeof(struct Duplex));
	for (int i = 0; i < dim; i++)
	{
		if (suprafataTotala(d[i]) >= 300) {
			verifica[j] = copiereDuplex(d[i]);
			j++;
		}
		else {
			nuVerifica[k] = copiereDuplex(d[i]);
			k++;
		}
	}
}

struct Duplex* concateneazaVectori(struct Duplex* vector1, int dim1, struct Duplex* vector2, int dim2) {

	int dimTotala = dim1 + dim2;
	struct Duplex* vectorNou = (struct Duplex*)malloc(dimTotala * sizeof(struct Duplex));
	for (int i = 0; i < dim1; i++) {
		vectorNou[i] = copiereDuplex(vector1[i]);
	}
	for (int i = 0; i < dim2; i++) {
		int indexNou = dim1 + i;
		vectorNou[indexNou] = copiereDuplex(vector2[i]);
	}

	return vectorNou;
}

int main()
{
	const char* locatii[] = { "Bucuresti", "Targoviste", "Pitesti", "Ploiesti", "Iasi" };
	struct Duplex* vectorDuplex = (struct Duplex*)malloc(5 * sizeof(struct Duplex));
	for (int i = 0; i < 5; i++)
	{
		vectorDuplex[i].codPostal = 1000 * (5 + i);
		vectorDuplex[i].locatie = (char*)malloc(100 * sizeof(char));
		strcpy(vectorDuplex[i].locatie, locatii[i]);
		vectorDuplex[i].nrEtaje = i + 1;
		vectorDuplex[i].suprafeteEtaje = (float*)malloc(vectorDuplex[i].nrEtaje * sizeof(float));
		for (int j = 0; j < vectorDuplex[i].nrEtaje; j++) {
			vectorDuplex[i].suprafeteEtaje[j] = (i + 1) * (j + 1) * 10;
		}
	}

	for (int i = 0; i < 5; i++)
		afisareDuplex(vectorDuplex[i]);
	printf("\n--------------------\n");
	struct Duplex* vectorNou = vectorMinim2Etaje(vectorDuplex, 5);
	printf("\n--------------------\n");
	struct Duplex* vectorDuplex2 = (struct Duplex*)malloc(2 * sizeof(struct Duplex));
	for (int i = 0; i < 2; i++)
	{
		vectorDuplex2[i].codPostal = 2000 * (5 + i);
		vectorDuplex2[i].locatie = (char*)malloc(100 * sizeof(char));
		strcpy(vectorDuplex2[i].locatie, locatii[i + 3]);
		vectorDuplex2[i].nrEtaje = i + 1;
		vectorDuplex2[i].suprafeteEtaje = (float*)malloc(vectorDuplex2[i].nrEtaje * sizeof(float));
		for (int j = 0; j < vectorDuplex2[i].nrEtaje; j++) {
			vectorDuplex2[i].suprafeteEtaje[j] = (i + 1) * (j + 1) * 20;
		}
	}

	printf("\nVectorul 1:\n");
	for (int i = 0; i < 3; i++)
		afisareDuplex(vectorDuplex[i]);

	printf("\nVectorul 2:\n");
	for (int i = 0; i < 2; i++)
		afisareDuplex(vectorDuplex2[i]);

	struct Duplex* vectorConcatenat = concateneazaVectori(vectorDuplex, 5, vectorDuplex2, 2);

	printf("\nVectorul concatenat:\n");
	for (int i = 0; i < 5; i++)
		afisareDuplex(vectorConcatenat[i]);
	return 0;
}
