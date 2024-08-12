#include <stdio.h>
#include <omp.h>

int main()
{
    int dado = 0;            // Variável compartilhada para armazenar o dado
    int dado_disponivel = 0; // Flag para indicar que o dado está disponível

#pragma omp parallel shared(dado, dado_disponivel)
    {
        int id = omp_get_thread_num();

        if (id == 0)
        {
            for (int i = 1; i <= 10; i++)
            {
                dado = i;
                printf("Produtor: dado = %d\n", dado);

#pragma omp flush(dado)

                dado_disponivel = 1;
#pragma omp flush(dado_disponivel)

                while (dado_disponivel == 1)
                {
#pragma omp flush(dado_disponivel)
                }
            }
        }
        else
        {
            while (1)
            {
#pragma omp flush(dado_disponivel)
                if (dado_disponivel == 1)
                {
#pragma omp flush(dado)
                    printf("Consumidor %d: processando dado = %d\n", id, dado);

                    dado_disponivel = 0;
#pragma omp flush(dado_disponivel)
                }

                if (dado >= 10)
                {
                    break;
                }
            }
        }
    }

    return 0;
}
