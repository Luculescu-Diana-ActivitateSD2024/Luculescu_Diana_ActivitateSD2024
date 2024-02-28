#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

struct Duplex
{
	int codPostal;
	char* locatie;
	int nrEtaje;
	float* suprafeteEtaje;
};

struct Duplex citire()
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

void afisare(const struct Duplex d) {
	printf("\nCod postal: %d", d.codPostal);
	printf("\nLocatie: %s", d.locatie);
	printf("Numar etaje: %d", d.nrEtaje);

	if (d.nrEtaje > 0) {
		printf("\nSuprafete etaje:");
		for (int i = 0; i < d.nrEtaje; ++i) {
			printf("\n Etaj %d: %.2f mp", i + 1, d.suprafeteEtaje[i]);
		}
	}
	printf("\n");
}

float suprafataTotala(const struct Duplex d) {
	float suprafataTotala = 0;
	for (int i = 0; i < d.nrEtaje; i++) {
		suprafataTotala += d.suprafeteEtaje[i];
	}
	return suprafataTotala;
}

void modificareCodPostal(struct Duplex* d, int newCodPostal) {
	d->codPostal = newCodPostal;
}


int main()
{
	struct Duplex d1 = citire();
	printf("\nDatele duplexului citit:\n"); afisare(d1);
	printf("\nSuprafata totala a duplexului: %.2f mp\n", suprafataTotala(d1));
	modificareCodPostal(&d1, 111111);
	printf("\nCodul postal dupa modificare: %d", d1.codPostal);
	printf("\nDatele duplexului dupa modificare:\n"); afisare(d1);
	free(d1.locatie);
	free(d1.suprafeteEtaje);
	return 0;
}
