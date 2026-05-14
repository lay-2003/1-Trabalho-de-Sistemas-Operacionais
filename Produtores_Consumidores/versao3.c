#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAM_BUFFER 5

int buffer[TAM_BUFFER];
int fim = 0;

void* produtor(void* arg) {

    int id = *(int*)arg;

    for(int i = 0; i < 10; i++) {

        int valor = rand() % 100;

        buffer[fim] = valor;

        printf("[PRODUTOR %d] inseriu %d na posição %d\n", id, valor, fim);

        fim = (fim + 1) % TAM_BUFFER;

        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {

    pthread_t p1, p2;

    int id1 = 1;
    int id2 = 2;

    pthread_create(&p1, NULL, produtor, &id1);
    pthread_create(&p2, NULL, produtor, &id2);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}

/*
Problemas Observados
Sem sincronização:
dois produtores podem acessar a mesma posição;
valores podem ser sobrescritos;
o buffer fica inconsistente.*/
