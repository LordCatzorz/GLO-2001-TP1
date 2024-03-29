#include <stdio.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 4

typedef struct
{
	int threadNum;
	int n;
	int debut;
	int fin;
	unsigned long long produit;
} Parametres;

void *CalculerProduit(void *data)
{
	Parametres *mesParametres = data;
	printf("Je suis le thread %d qui calcul le produit de %d a %d\n",
		mesParametres->threadNum, 
		mesParametres->debut,
		mesParametres->fin);

	mesParametres->produit = 1;
	for (mesParametres->n = mesParametres->debut; mesParametres->n <= mesParametres->fin; mesParametres->n++)
	{
		mesParametres->produit *= mesParametres->n;
	} 
	pthread_exit(&mesParametres->produit); //&mesParametres->produit ou NULL ??
}

void InitialiseParam(Parametres *param, int num, int start, int end)
{
	param->threadNum = num;
	param->debut = start;
	param->fin = end;
	param->n = 0;
	param->produit = 1;
}

void PrintFactorial(int factorialToCalculate)
{
	printf("Calcul du factorielle de %d\n", factorialToCalculate);

	pthread_t threads[NUMBER_OF_THREADS];
	Parametres mesParametres[NUMBER_OF_THREADS];
	
	int startValue = 1;
	int endValue = 1;
	int step = factorialToCalculate / NUMBER_OF_THREADS;

	for (int i = 0; i < NUMBER_OF_THREADS -1; i++)
	{
		endValue = startValue + step - 1;
		InitialiseParam(&mesParametres[i], i + 1, startValue, endValue);
		startValue = endValue + 1;
	}
	//Forcer le dernier thread a prendre les cas restants.
	InitialiseParam(&mesParametres[NUMBER_OF_THREADS - 1], NUMBER_OF_THREADS, startValue, factorialToCalculate);
	
	for(int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		printf("Main(): en train de creer thread %d\n", i+1);
		pthread_create(&threads[i], NULL, CalculerProduit, (void *)&mesParametres[i]);
	}

	for(int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		pthread_join(threads[i], NULL); //NULL ou value??	
	}

	printf("Main(): Tous les threads ont termines! Je calcul la factorielle...\n");

	long long fact = 1;
	fact *= mesParametres[0].produit;
	fact *= mesParametres[1].produit;
	fact *= mesParametres[2].produit;
	fact *= mesParametres[3].produit;

	printf("Main(): La factorielle de %d est %llu\n", factorialToCalculate, fact);
}

int main(int argc, char *argv[]) 
{ 
	const int factorialToCalculate = 15;
	//for(int zzz=0; zzz<50000;zzz++)
	//{
		PrintFactorial(factorialToCalculate);
	//}
	return 0;
}
