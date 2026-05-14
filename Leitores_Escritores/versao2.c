#include <stdio.h>

    sleep(1);

    sem_wait(&mutex);

    leitoresAtivos--;

    if(leitoresAtivos == 0)
        sem_post(&db);

    sem_post(&mutex);

    printf("[LEITOR %d] saiu da região crítica\n", id);
    printf("[LEITOR %d] finalizado\n", id);

    pthread_exit(NULL);
}

void* escritor(void* arg) {

    int id = *(int*)arg;

    printf("[ESCRITOR %d] criado\n", id);

    sleep(rand() % 5);

    printf("[ESCRITOR %d] aguardando região crítica\n", id);

    sem_wait(&db);

    printf("[ESCRITOR %d] entrou na região crítica\n", id);

    int novaNota = rand() % 101;

    notaCompartilhada = novaNota;

    printf("[ESCRITOR %d] atualizou nota para %d\n", id, novaNota);

    sleep(2);

    printf("[ESCRITOR %d] saiu da região crítica\n", id);

    sem_post(&db);

    printf("[ESCRITOR %d] finalizado\n", id);

    pthread_exit(NULL);
}

int main() {

    pthread_t leitores[5], escritores[3];

    int idLeitor[5];
    int idEscritor[3];

    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

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

    sem_destroy(&mutex);
    sem_destroy(&db);

    return 0;
}

/*
Nesta implementação:
-escritores possuem prioridade;
-leitores só acessam quando não há escritores ativos;
-não ocorre leitura suja.

-Explicação da Solução
Foram utilizados dois semáforos:

-Semáforo mutex
Protege a variável:
leitoresAtivos

-Semáforo db
Controla o acesso à região crítica.
Somente:
-vários leitores OU
-um escritor
podem acessar os dados.*/
