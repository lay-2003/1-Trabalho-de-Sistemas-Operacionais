#include <stdio.h>
        fim = (fim + 1) % TAM_BUFFER;

        mostrarBuffer();

        sem_post(&mutex);
        sem_post(&cheio);

        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

void* consumidor(void* arg) {

    int id = *(int*)arg;

    for(int i = 0; i < 15; i++) {

        sem_wait(&cheio);
        sem_wait(&mutex);

        int item = buffer[inicio];
        buffer[inicio] = 0;

        inicio = (inicio + 1) % TAM_BUFFER;

        printf("[CONSUMIDOR %d] consumiu %d\n", id, item);

        mostrarBuffer();

        sem_post(&mutex);
        sem_post(&vazio);

        sleep(rand() % 4);
    }

    pthread_exit(NULL);
}

int main() {

    pthread_t produtores[3], consumidor1;

    int idProd[3] = {1,2,3};
    int idCons = 1;

    sem_init(&vazio, 0, TAM_BUFFER);
    sem_init(&cheio, 0, 0);
    sem_init(&mutex, 0, 1);

    for(int i = 0; i < 3; i++)
        pthread_create(&produtores[i], NULL, produtor, &idProd[i]);

    pthread_create(&consumidor1, NULL, consumidor, &idCons);

    for(int i = 0; i < 3; i++)
        pthread_join(produtores[i], NULL);

    pthread_join(consumidor1, NULL);

    sem_destroy(&vazio);
    sem_destroy(&cheio);
    sem_destroy(&mutex);

    return 0;
}

/*Explicação da Solução

Foram utilizados três semáforos.

-Semáforo vazio

Controla posições livres no buffer.

-Semáforo cheio

Controla posições ocupadas.

-Semáforo mutex

Garante exclusão mútua no acesso ao buffer. */
