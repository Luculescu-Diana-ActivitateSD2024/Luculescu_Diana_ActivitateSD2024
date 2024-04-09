#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Mail Mail;
struct Mail {
	char* text;
	int prioritate;
};

typedef struct Heap Heap;
struct Heap {
	Mail* vector;
	int dim;
};

Heap initializareHeap(int dim)
{
	Heap heap;
	heap.vector = (Mail*)malloc(dim * sizeof(Mail));
	heap.dim = dim;
	return heap;
}

Mail initializareMesaj(const char* text, int prioritate)
{
	Mail mail;
	mail.text = (char*)malloc(strlen(text) + 1);
	strcpy(mail.text, text);
	mail.prioritate = prioritate;
	return mail;
}

void afisareMail(Mail mail)
{
	printf("Mail cu textul: %s si grad de prioritate: %d\n", mail.text, mail.prioritate);
}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.dim; i++)
	{
		afisareMail(heap.vector[i]);
	}
}

void filtrare(Heap heap, int pozitieRadacina)
{
	int pozitieFiuStanga = pozitieRadacina * 2 + 1;
	int pozitieFiuDreapta = pozitieRadacina * 2 + 2;
	int pozitieMaxima = pozitieRadacina;

	if (pozitieFiuStanga < heap.dim && heap.vector[pozitieMaxima].prioritate<heap.vector[pozitieFiuStanga].prioritate)
	{
		pozitieMaxima = pozitieFiuStanga;
	}

	if (pozitieFiuDreapta < heap.dim && heap.vector[pozitieMaxima].prioritate < heap.vector[pozitieFiuDreapta].prioritate)
	{
		pozitieMaxima = pozitieFiuDreapta;
	}

	if (pozitieMaxima != pozitieRadacina)
	{
		if (heap.vector[pozitieRadacina].prioritate < heap.vector[pozitieMaxima].prioritate)
		{
			Mail aux = heap.vector[pozitieRadacina];
			heap.vector[pozitieRadacina] = heap.vector[pozitieMaxima];
			heap.vector[pozitieMaxima] = aux;

			if (pozitieMaxima < (heap.dim - 2) / 2)
			{
				filtrare(heap, pozitieMaxima);
			}

		}
	}
		
}

Mail extragereMax(Heap* heap)
{
	if (heap->dim > 0)
	{
		Mail extras = (*heap).vector[0];

		Mail* aux = (Mail*)malloc(sizeof(Mail) * ((*heap).dim - 1));
		for (int i = 0; i < heap->dim; i++)
		{
			aux[i - 1] = heap->vector[i];
		}

		free(heap->vector);
		heap->vector = aux;

		heap->dim--;

		for (int i = (heap->dim - 2) / 2; i >= 0; i--)
		{
			filtrare((*heap), i);
		}

		return extras;
	}
	
}

void inserareMailInHeap(Heap* heap,Mail mail)
{
	Mail* aux = (Mail*)malloc(sizeof(Mail) * (heap->dim + 1));

	aux[0] = mail;
	for (int i = 1; i < heap->dim+1; i++)
	{
		aux[i] = heap->vector[i-1];
	}
	free(heap->vector);
	heap->vector = aux;
	heap->dim++;

	filtrare((*heap), 0);
	
}

void dezalocareHeap(Heap* heap)
{
	for (int i = 0; i < heap->dim; i++)
	{
		free(heap->vector[i].text);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->dim = 0;
}

void main() {
	Heap heap=initializareHeap(6);

	heap.vector[0] = initializareMesaj("Salut1", 7);
	heap.vector[1] = initializareMesaj("Salut2", 9);
	heap.vector[2] = initializareMesaj("Salut3", 3);
	heap.vector[3] = initializareMesaj("Salut4", 8);
	heap.vector[4] = initializareMesaj("Salut5", 6);
	heap.vector[5] = initializareMesaj("Salut6", 10);

	afisareHeap(heap);

	for (int i = (heap.dim - 2) / 2; i >= 0; i--)
	{
		filtrare(heap, i);
	}

	printf("--------------------\n");
	afisareHeap(heap);
	printf("--------------------\n");
	//de preferat extragem in cadrul unor obiecte pe care sa le putem sterge
	printf("Elemente extrase:\n");
	afisareMail(extragereMax(&heap));

	printf("Inserare:\n");
	inserareMailInHeap(&heap, initializareMesaj("Buna", 6));
	inserareMailInHeap(&heap, initializareMesaj("Buna2", 10));

	afisareHeap(heap);

	dezalocareHeap(&heap);

}