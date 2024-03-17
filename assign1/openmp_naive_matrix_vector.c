#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void matrixVectorMul(int **matrix, int *vector, int *result, int matrixSize, int vectorSize) {
    #pragma omp parallel for
    for (int i = 0; i < matrixSize; i++) {
        result[i] = 0;
        for (int j = 0; j < vectorSize; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <matrix size> <vector size>\n", argv[0]);
        return 1;
    }

    int matrixSize = atoi(argv[1]);
    int vectorSize = atoi(argv[2]);

    srand(time(NULL));

    int **matrix = (int **)malloc(matrixSize * sizeof(int *));
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = (int *)malloc(vectorSize * sizeof(int));
        for (int j = 0; j < vectorSize; j++) {
            matrix[i][j] = rand() % 10; // Fill with random values between 0 and 9
        }
    }

    int *vector = (int *)malloc(vectorSize * sizeof(int));
    for (int i = 0; i < vectorSize; i++) {
        vector[i] = rand() % 10; // Fill with random values between 0 and 9
    }

    int *result = (int *)malloc(matrixSize * sizeof(int));

    matrixVectorMul(matrix, vector, result, matrixSize, vectorSize);

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
