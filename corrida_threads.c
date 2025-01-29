#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5
#define DISTANCIA 100

typedef struct {
    int id;
    int progresso;
} ThreadData;

pthread_barrier_t barreira;
pthread_mutex_t mutex;

void *corrida(void *arg) {
    ThreadData *dados = (ThreadData *)arg;

    pthread_barrier_wait(&barreira);

    printf("Thread-%d começou a corrida!\n", dados->id);

    while (dados->progresso < DISTANCIA) {
        dados->progresso += rand() % 10 + 1;
        if (dados->progresso > DISTANCIA) {
            dados->progresso = DISTANCIA;
        }

        pthread_mutex_lock(&mutex);
        printf("Thread-%d progresso: [", dados->id);
        for (int i = 0; i < dados->progresso * 10 / DISTANCIA; i++) {
            printf("#");
        }
        for (int i = dados->progresso * 10 / DISTANCIA; i < 10; i++) {
            printf(" ");
        }
        printf("] %d%%\n", dados->progresso * 100 / DISTANCIA);
        fflush(stdout);
        pthread_mutex_unlock(&mutex);

        usleep((rand() % 400 + 100) * 1000);
    }

    printf("Thread-%d cruzou a linha de chegada!\n", dados->id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData dados[NUM_THREADS];

    srand(time(NULL));

    if (pthread_barrier_init(&barreira, NULL, NUM_THREADS) != 0) {
        perror("Erro ao inicializar barreira");
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        dados[i].id = i + 1;
        dados[i].progresso = 0;

        if (pthread_create(&threads[i], NULL, corrida, &dados[i]) != 0) {
            perror("Erro ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nA corrida terminou!\n");

    pthread_barrier_destroy(&barreira);
    pthread_mutex_destroy(&mutex);

    return 0;
}
