#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000
#define MAX_VAL 100

int main()
{
    int vetor[N];
    int histograma[MAX_VAL] = {0};

    for (int i = 0; i < N; i++)
    {
        vetor[i] = rand() % MAX_VAL;
    }

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        int valor = vetor[i];

#pragma omp critical
        {
            histograma[valor]++;
        }
    }

    printf("Histograma:\n");
    for (int i = 0; i < MAX_VAL; i++)
    {
        printf("Valor %d: %d ocorrências\n", i, histograma[i]);
    }

    return 0;
}
