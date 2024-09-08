    #include <stdio.h>
    #include <pthread.h>
    #include <unistd.h>
    #include <stdlib.h>
    #define RESET "\033[0m"  // reset para a cor padrão
    #define RED "\033[31m"   // cor vermelha
    #define GREEN "\033[32m" // cor verde
    #define YELLOW "\033[33m"
    #define NUM_CARS 4
    #define TRUE 1
    #define FALSE 0
    int semaforo = 0;
    char *cor_semaforoVertical;
    char *cor_semaforoHorizontal;

    pthread_mutex_t mutex;
    int posicoes_carros[NUM_CARS] = {-1};

    char ruaVertical[6] = {' ', ' ', ' ', ' ', ' ', ' '};
    char ruaHorizontal[6] = {' ', ' ', ' ', ' ', ' ', ' '};

    void *transito()
    {
        while (1)
        {
            for (int i = 0; i < 5; i++)
            {
                ruaVertical[i] = ' ';
                ruaHorizontal[i] = ' ';
            }
            pthread_mutex_lock(&mutex);

            for (int i = 0; i < NUM_CARS; i++)
            {
                if (posicoes_carros[i] >= 0 && posicoes_carros[i] < 5)
                {
                    if (i == 0)
                    {
                        ruaHorizontal[posicoes_carros[i]] = '1';
                    }
                    else if (i == 1)
                    {
                        ruaVertical[posicoes_carros[i]] = '2';
                    }
                    else if (i == 2)
                    {
                        ruaHorizontal[posicoes_carros[i]] = '3';
                    }
                    else if (i == 3)
                    {
                        ruaVertical[posicoes_carros[i]] = '4';
                    }
                }
            }

            pthread_mutex_unlock(&mutex);

            if (semaforo == 0)
            {
                cor_semaforoVertical = RED;
                cor_semaforoHorizontal = GREEN;
            }
            else
            {
                cor_semaforoHorizontal = RED;
                cor_semaforoVertical = GREEN;
            }

            printf("\n\n");
            printf("               rua 1\n");
            printf("             +      +\n");
            printf("             |  %c   |\n", ruaVertical[0]);
            printf("             +------+\n");
            printf("             |  %c   |\n", ruaVertical[1]);
            printf("      +--+---+%s------\033[39m+---+--+\n", cor_semaforoVertical);
            printf("rua 4  %c | %c %s|\033[39m   %c%c | %c | %c  rua 2\n", ruaHorizontal[0], ruaHorizontal[1], cor_semaforoHorizontal, ruaVertical[2], ruaHorizontal[2], ruaHorizontal[3], ruaHorizontal[4]);
            printf("      +--+---+------+---+--+\n");
            printf("             |  %c   |\n", ruaVertical[3]);
            printf("             +------+\n");
            printf("             |  %c   |\n", ruaVertical[4]);
            printf("             +      +\n");
            printf("               rua 3\n\n\n");

            usleep(199000);
            system("clear");
        }

        pthread_exit(0);
    }

    void *car_thread(void *thread_id)
    {
        long tid;
        tid = (long)thread_id;

        // Defina a direção do carro (0 para horizontal, 1 para vertical)
        int direcao_carro = (tid % 2 == 0) ? 0 : 1;
        int vaiOuNaovaiVaiouNaoVai = TRUE;
        int auxvaiOuNaoVaiIncremento = 0;
        while (1)
        {
            pthread_mutex_lock(&mutex);

            // Verifica se o semáforo permite a passagem na direção do carro
            if (direcao_carro == 0)
            {
                // Verifica se há outro carro na mesma posição
                for (int i = 0; i < NUM_CARS; i++)
                {
                    if (i != tid && posicoes_carros[tid] == posicoes_carros[i] && posicoes_carros[i] == 1)
                    {
                        semaforo = 0;
                    }
                }

                if ((posicoes_carros[tid] < 5 && semaforo == 0) && (ruaHorizontal[posicoes_carros[tid] + 1] == ' '))
                {
                    if (vaiOuNaovaiVaiouNaoVai == TRUE)
                    {
                        if (posicoes_carros[tid] != 4) {
                            posicoes_carros[tid]++;
                        } else if ((ruaHorizontal[0] == ' ') && (posicoes_carros[2] != 0)) {
                            posicoes_carros[tid]++;
                        }
                    }
                    else
                        auxvaiOuNaoVaiIncremento++;
                }
                else if ((posicoes_carros[tid] < 5 && semaforo == 1 && posicoes_carros[tid] != 1) && (ruaHorizontal[posicoes_carros[tid] + 1] == ' '))
                {
                    if (vaiOuNaovaiVaiouNaoVai == TRUE)
                    {
                        if (posicoes_carros[tid] != 4) {
                            posicoes_carros[tid]++;
                        } else if ((ruaHorizontal[0] == ' ') && (posicoes_carros[2] != 0)) {
                            posicoes_carros[tid]++;
                        }
                    }
                    else
                        auxvaiOuNaoVaiIncremento++;
                }

                if (posicoes_carros[tid] >= 5 || auxvaiOuNaoVaiIncremento >= 5)
                {

                    if (tid <= 1) {
                        posicoes_carros[tid] = 0;
                    }
                    auxvaiOuNaoVaiIncremento = -1;
                    if (tid > 1  && posicoes_carros[0] == 1 || posicoes_carros[0] == 2 || posicoes_carros[0] == 3)
                    {
                        srand(time(NULL));
                        double random_number = (double)rand() / RAND_MAX; 
                        double threshold = 0.6;                          
                        if (random_number < threshold)
                        {
                            posicoes_carros[tid] = -1;
                            vaiOuNaovaiVaiouNaoVai = FALSE; 
                        }
                        else
                        {
                            posicoes_carros[tid] = 0;
                            vaiOuNaovaiVaiouNaoVai = TRUE; 
                        }
                    }
                } 
            }
            else if (direcao_carro == 1)
            {
                // Verifica se há outro carro na mesma posição
                for (int i = 0; i < NUM_CARS; i++)
                {
                    if (i != tid && posicoes_carros[tid] == posicoes_carros[i] && posicoes_carros[i] == 1)
                    {
                        semaforo = 1;
                    }
                }

                if ((posicoes_carros[tid] < 5 && semaforo == 1) && (ruaVertical[posicoes_carros[tid] + 1] == ' '))
                {
                    if (vaiOuNaovaiVaiouNaoVai == TRUE)
                    {
                        if (posicoes_carros[tid] != 4) {
                            posicoes_carros[tid]++;
                        } else if ((ruaVertical[0] == ' ') && (posicoes_carros[3] != 0)) {
                            posicoes_carros[tid]++;
                        }
                    }
                    else 
                        auxvaiOuNaoVaiIncremento++;
                }
                else if ((posicoes_carros[tid] < 5 && semaforo == 0 && posicoes_carros[tid] != 1) && (ruaVertical[posicoes_carros[tid] + 1] == ' '))
                {
                    if (vaiOuNaovaiVaiouNaoVai == TRUE)
                    {
                        if (posicoes_carros[tid] != 4) {
                            posicoes_carros[tid]++;
                        } else if ((ruaVertical[0] == ' ') && (posicoes_carros[3] != 0)) {
                            posicoes_carros[tid]++;
                        }
                    }
                    else
                        auxvaiOuNaoVaiIncremento++;
                }

                if (posicoes_carros[tid] >= 5 || auxvaiOuNaoVaiIncremento >= 5)
                {
                    if (tid <= 1) {
                        posicoes_carros[tid] = 0;
                    }
                    auxvaiOuNaoVaiIncremento = -1;
                    if (tid > 1 && posicoes_carros[1] == 1 || posicoes_carros[1] == 2 || posicoes_carros[1] == 3)
                    {
                        srand(time(NULL));
                        double random_number = (double)rand() / RAND_MAX; 
                        double threshold = 0.6;                           
                        if (random_number < threshold)
                        {
                            posicoes_carros[tid] = -1;
                            vaiOuNaovaiVaiouNaoVai = FALSE; 
                        }
                        else
                        {
                            posicoes_carros[tid] = 0;
                            vaiOuNaovaiVaiouNaoVai = TRUE; 
                        }
                    }
                }
            }

            pthread_mutex_unlock(&mutex);
            usleep(900000);
        }
    }

    int main()
    {
        pthread_t cars[NUM_CARS];

        for (int i = 0; i < NUM_CARS; i++)
        {
            if (i == 0)
            {
                posicoes_carros[i] = 0;
            }
            else if (i == 1)
            {
                posicoes_carros[i] = 0;
            }
            else if (i == 2)
            {
                posicoes_carros[i] = -1;
            }
            else if (i == 3)
            {
                posicoes_carros[i] = -1;
            }
        }
        int rc;
        long t;
        pthread_mutex_init(&mutex, NULL);
        pthread_t t_trafego;

        pthread_create(&t_trafego, NULL, transito, NULL);
        // Cria threads representando carros
        for (t = 0; t < NUM_CARS; t++)
        {
            rc = pthread_create(&cars[t], NULL, car_thread, (void *)t);
        }

        for (int i = 0; i < NUM_CARS; i++)
        {
            pthread_join(cars[i], NULL);
        }

        pthread_cancel(t_trafego); // Cancela a thread do sistema de tráfego para finalizar o programa

        pthread_mutex_destroy(&mutex);
        return 0;
    }