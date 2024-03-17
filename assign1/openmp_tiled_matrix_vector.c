#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void matrixVectorMul(int **matrix, int *vector, int *result, int matrixSize, int tileSize) {
    #pragma omp parallel for
    for (int i = 0; i < matrixSize; i++) {
        result[i] = 0;
        for (int j = 0; j < matrixSize; j += tileSize) {
            int sum = 0;
            for (int k = 0; k < tileSize; k++) {
                sum += matrix[i][j + k] * vector[j + k];
            }
            result[i] += sum;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <matrix size> <tile size>\n", argv[0]);
        return 1;
    }

    int matrixSize = atoi(argv[1]);
    int tileSize = atoi(argv[2]);

    srand(time(NULL));

    int **matrix = (int **)malloc(matrixSize * sizeof(int *));
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (int *)malloc(matrixSize * sizeof(int));
        for (int j = 0; j < matrixSize; j++) {
            matrix[i][j] = rand() % 10; // Fill with random values between 0 and 9
        }
    }

    int *vector = (int *)malloc(matrixSize * sizeof(int));
    for (int i = 0; i < matrixSize; i++) {
        vector[i] = rand() % 10; // Fill with random values between 0 and 9
    }

    int *result = (int *)malloc(matrixSize * sizeof(int));

    matrixVectorMul(matrix, vector, result, matrixSize, tileSize);

    printf("Result:\n");
    for (int i = 0; i < matrixSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    for (int i = 0; i < matrixSize; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    return 0;
}
