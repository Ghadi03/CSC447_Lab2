#include <stdio.h>
#include <omp.h>

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

int main() {
    double start_time = omp_get_wtime();
    printf("Max threads: %d\n", omp_get_max_threads());
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            int result = 0;

            for (int k = 0; k < N; k++) {
                result += A[i][k] * B[k][j];
            }

            C[i][j] = result;
        }
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    printf("Result:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
