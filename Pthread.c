#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 3
#define N 3
#define P 3

int A[M][N] = { {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9} };

int B[N][P] = { {9, 8, 7},
                {6, 5, 4},
                {3, 2, 1} };

int C[M][P];

typedef struct {
    int row;
    int col;
} pos;

void *matrix_multiply(void *arg) {
    pos *data = (pos *)arg;
    int result = 0;

    for (int k = 0; k < N; k++) {
        result += A[data->row][k] * B[k][data->col];
    }

    C[data->row][data->col] = result;

    pthread_exit(0);
}

int main() {
    pthread_t threads[M * P];
    int thread_count = 0;

    clock_t start = clock();

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            pos *data = (pos *)malloc(sizeof(pos));
            data->row = i;
            data->col = j;

            pthread_create(&threads[thread_count], NULL, matrix_multiply, (void *)data);
            pthread_join(threads[thread_count], NULL);
            thread_count++;
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Result:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}

