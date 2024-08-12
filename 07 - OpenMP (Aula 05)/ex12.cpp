#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define NUM_POINTS 1000000

int main()
{
    int pontos_dentro_circulo = 0;
    int total_pontos = NUM_POINTS;

#pragma omp parallel
    {
        int pontos_dentro_local = 0;
        unsigned int seed = 12345 + omp_get_thread_num();
        srand(seed);

#pragma omp for reduction(+ : pontos_dentro_circulo)
        for (int i = 0; i < total_pontos; i++)
        {
            double x = rand() / (double)RAND_MAX;
            double y = rand() / (double)RAND_MAX;

            if (x * x + y * y <= 1.0)
            {
                pontos_dentro_local++;
            }
        }

        pontos_dentro_circulo += pontos_dentro_local;

#pragma omp barrier
#pragma omp single
        {
            double pi = 4.0 * (double)pontos_dentro_circulo / total_pontos;
            printf("Aproximação de Pi: %f\n", pi);
        }
    }

    return 0;
}
