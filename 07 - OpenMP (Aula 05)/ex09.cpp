#include <stdio.h>
#include <omp.h>

#define N 10

int main()
{
    int vetor[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int contagem_pares = 0;
    int contagem_impares = 0;

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        if (vetor[i] % 2 == 0)
        {
#pragma omp atomic
            contagem_pares++;
        }
        else
        {
#pragma omp atomic
            contagem_impares++;
        }
    }

    printf("Número de elementos pares: %d\n", contagem_pares);
    printf("Número de elementos ímpares: %d\n", contagem_impares);

    return 0;
}
