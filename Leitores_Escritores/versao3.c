/*Nesta versão vários escritores modificam os dados simultaneamente.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int notaCompartilhada = 0;

void* escritor(void* arg) {

    int id = *(int*)arg;

    for(int i = 0; i < 5; i++) {

        int valorAntigo = notaCompartilhada;

        sleep(1);

        notaCompartilhada = valorAntigo + 10;

        printf("[ESCRITOR %d] nota = %d\n", id, notaCompartilhada);
    }

    pthread_exit(NULL);
}

int main() {

    pthread_t t1, t2;

    int id1 = 1;
    int id2 = 2;

    pthread_create(&t1, NULL, escritor, &id1);
    pthread_create(&t2, NULL, escritor, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Valor final: %d\n", notaCompartilhada);

    return 0;
}

/*Nesta versão ocorre condição de corrida.

Os escritores podem:

-ler o mesmo valor;
-atualizar simultaneamente;
-perder atualizações.

O resultado final pode ser diferente em cada execução.*/
