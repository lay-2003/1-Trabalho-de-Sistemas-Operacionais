/*Versão 2 – Vários Produtores e Vários Consumidores*/

#include <stdio.h>
        int item = rand() % 100;

        sem_wait(&vazio);
        sem_wait(&mutex);

        buffer[fim] = item;

        printf("[PRODUTOR %d] inseriu %d na posição %d\n", id, item, fim);

        fim = (fim + 1) % TAM_BUFFER;

        sem_post(&mutex);
        sem_post(&cheio);

        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

void* consumidor(void* arg) {

    int id = *(int*)arg;

    for(int i = 0; i < 5; i++) {

        sem_wait(&cheio);
        sem_wait(&mutex);

        int item = buffer[inicio];

        printf("[CONSUMIDOR %d] removeu %d da posição %d\n", id, item, inicio);

        buffer[inicio] = 0;

        inicio = (inicio + 1) % TAM_BUFFER;

        sem_post(&mutex);
        sem_post(&vazio);

        sleep(rand() % 4);
    }

    pthread_exit(NULL);
}

int main() {

    pthread_t produtores[3], consumidores[3];

    int idProd[3] = {1,2,3};
    int idCons[3] = {1,2,3};

    sem_init(&vazio, 0, TAM_BUFFER);
    sem_init(&cheio, 0, 0);
    sem_init(&mutex, 0, 1);

    for(int i = 0; i < 3; i++)
        pthread_create(&produtores[i], NULL, produtor, &idProd[i]);

    for(int i = 0; i < 3; i++)
        pthread_create(&consumidores[i], NULL, consumidor, &idCons[i]);

    for(int i = 0; i < 3; i++)
        pthread_join(produtores[i], NULL);

    for(int i = 0; i < 3; i++)
        pthread_join(consumidores[i], NULL);

    return 0;
}

