#include<stdio.h>
#include<malloc.h>


struct Cofetarie {
	char* nume; //nu mai avem string
	int nrAngajati;
	float* salarii;
};

void afisareCofetarie(struct Cofetarie c)
{

	if (c.nume != NULL) {
		printf("\nNume: %s", c.nume);
	}
	printf("\nNr. angajati: %d", c.nrAngajati);
	if (c.salarii != NULL) {
		printf("\nSalarii: ");
		for (int i = 0; i < c.nrAngajati; i++)
		{
			printf("%5.2f, ", c.salarii[i]);
		}
	}
	printf("\n");
}

struct Cofetarie initializareCofetarie(const char* nume, int nrAngajati, const float* salarii)
{
	struct Cofetarie c;
	c.nume = malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrAngajati = nrAngajati;
	c.salarii = malloc(sizeof(float) * nrAngajati);
	for (int i = 0; i < nrAngajati; i++)
	{
		c.salarii[i] = salarii[i];
	}
	return c;

}

void dezalocareMemorieCofetarie(struct Cofetarie* c)
{
	if (c->nume != NULL)
	{
		free(c->nume);
	}
	free(c->salarii);
	c->nume = NULL;
	c->salarii = NULL;
}

int main()
{
	struct Cofetarie cofetarie1;
	cofetarie1.nume = (char*)malloc((strlen("Dulce") + 1) * sizeof(char));//nu folosesc new; malloc primeste dim in bytes/octeti, returneaza un pointer general(la void)/la o adresa de memorie; un pointer ocupa 4 sau 8 bytes, char 1, float 4; malloc returneaza tipul void*
	strcpy(cofetarie1.nume, "Dulce");
	cofetarie1.nrAngajati = 3;
	cofetarie1.salarii = (float*)malloc(sizeof(float) * cofetarie1.nrAngajati);
	for (int i = 0; i < cofetarie1.nrAngajati; i++)
	{
		cofetarie1.salarii[i] = (i + 1) * 1000;
	}
	afisareCofetarie(cofetarie1);

	float* vector = malloc(sizeof(float) * 2);
	vector[0] = 3235;
	vector[1] = 4500;
	struct Cofetarie cofetarie2 = initializareCofetarie("Diana", 2, vector);
	afisareCofetarie(cofetarie2);

	//printf("%s", cofetarie1.nume);
	free(vector);
	/*free(cofetarie1.nume);
	free(cofetarie1.salarii);

	free(cofetarie2.nume);
	free(cofetarie2.salarii);*/
	dezalocareMemorieCofetarie(&cofetarie1);
	dezalocareMemorieCofetarie(&cofetarie2);
	afisareCofetarie(cofetarie1);

	return 0;
}