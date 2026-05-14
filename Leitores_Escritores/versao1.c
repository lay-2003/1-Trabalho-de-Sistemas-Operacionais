#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int notaCompartilhada = 0;

void* leitor(void* arg) {
    int id = *(int*)arg;

    printf("[LEITOR %d] criado\n", id);

    sleep(rand() % 3);

    printf("[LEITOR %d] lendo nota: %d\n", id, notaCompartilhada);

    printf("[LEITOR %d] finalizado\n", id);

    pthread_exit(NULL);
}

void* escritor(void* arg) {
    int id = *(int*)arg;

    printf("[ESCRITOR %d] criado\n", id);

    sleep(rand() % 4);

    int novaNota = rand() % 101;

    printf("[ESCRITOR %d] alterando nota para %d\n", id, novaNota);

    notaCompartilhada = novaNota;

    printf("[ESCRITOR %d] finalizado\n", id);

    pthread_exit(NULL);
}

int main() {

    pthread_t leitores[5], escritores[3];

    int idLeitor[5];
    int idEscritor[3];

    for(int i = 0; i < 5; i++) {
        idLeitor[i] = i + 1;
        pthread_create(&leitores[i], NULL, leitor, &idLeitor[i]);
    }

    for(int i = 0; i < 3; i++) {
        idEscritor[i] = i + 1;
        pthread_create(&escritores[i], NULL, escritor, &idEscritor[i]);
    }

    for(int i = 0; i < 5; i++)
        pthread_join(leitores[i], NULL);

    for(int i = 0; i < 3; i++)
        pthread_join(escritores[i], NULL);

    return 0;
}



/*Nesta versão não há proteção da região crítica.

Consequentemente:

leitores podem ler enquanto escritores atualizam;
valores inconsistentes podem ser exibidos;
ocorre leitura suja.*/
