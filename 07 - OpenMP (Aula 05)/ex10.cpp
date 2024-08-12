#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int vetor[N];
    int i;

    for (i = 0; i < N; i++)
    {
        vetor[i] = i + 1;
    }

#pragma omp parallel shared(vetor) private(i)
    {
// Etapa 1: Multiplica cada elemento do vetor por 2
#pragma omp for
        for (i = 0; i < N; i++)
        {
            vetor[i] *= 2;
            printf("Thread %d - Etapa 1: vetor[%d] = %d\n", omp_get_thread_num(), i, vetor[i]);
        }

// Sincronização de todas as threads
#pragma omp barrier

// Etapa 2: Soma 10 a cada elemento do vetor
#pragma omp for
        for (i = 0; i < N; i++)
        {
            vetor[i] += 10;
            printf("Thread %d - Etapa 2: vetor[%d] = %d\n", omp_get_thread_num(), i, vetor[i]);
        }
    }

    printf("Vetor final: ");
    for (i = 0; i < N; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
