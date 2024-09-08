#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>

pthread_mutex_t mutex;

void* transito(){
    int i = 0;
    while(1){
        //srand(time(NULL));
        //int qual_rua = rand() % 4;
        int rua[5] = {32, 32, 32, 32, 32};

        rua[i % 5] = 67;
        i = i + 1;
        
        //printf("rua: %i", qual_rua);


        printf("\n\n");
        printf("               rua 1\n");
        printf("             +      +\n");
        printf("             |  %c   |\n", rua[0]);
        printf("             +------+\n");
        printf("             |  %c   |\n", rua[1]);
        printf("      +--+---+\033[32m------\033[39m+---+--+\n");
        printf("rua 4    | C \033[31m|\033[39m  %c   |   |    rua 2\n", rua[2]);
        printf("      +--+---+------+---+--+\n");
        printf("             |  %c   |\n", rua[3]);
        printf("             +------+\n");
        printf("             |  %c   |\n", rua[4]);
        printf("             +      +\n");
        printf("               rua 3\n\n\n");
        usleep(199000);
        system("clear");
    }

    pthread_exit(0);
}

int main() {
    system("clear");
    pthread_t t1, t2;

    pthread_create(&t1, NULL, transito, NULL);    
    pthread_join(t1, NULL);

    return 0;
}