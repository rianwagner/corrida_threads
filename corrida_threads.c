#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5
#define DISTANCIA 100

typedef struct {
    int id;
    int *resultados;
    int *posicao_atual;
    pthread_mutex_t *mutex;
} ThreadData;

void *corrida(void *arg) {
    ThreadData *dados = (ThreadData *)arg;
    int progresso = 0;

    printf("Thread-%d começou a corrida!\n", dados->id);
    while (progresso < DISTANCIA) {
        progresso += rand() % 10 + 1;
        usleep((rand() % 400 + 100) * 1000);
    }

    pthread_mutex_lock(dados->mutex);
    dados->resultados[*dados->posicao_atual] = dados->id;
    (*dados->posicao_atual)++;
    pthread_mutex_unlock(dados->mutex);

    printf("Thread-%d cruzou a linha de chegada!\n", dados->id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData dados[NUM_THREADS];
    int resultados[NUM_THREADS];
    int posicao_atual = 0;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++) {
        dados[i].id = i + 1;
        dados[i].resultados = resultados;
        dados[i].posicao_atual = &posicao_atual;
        dados[i].mutex = &mutex;

        if (pthread_create(&threads[i], NULL, corrida, &dados[i]) != 0) {
            perror("Erro ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nA corrida terminou!\n");
    printf("Classificação:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%dº lugar: Thread-%d\n", i + 1, resultados[i]);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
