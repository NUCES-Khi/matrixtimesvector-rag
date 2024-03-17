#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void matrixVectorMul(int **matrix, int *vector, int *result, int matrixSize, int tileSize, int rank, int size) {
    int local_start = rank * (matrixSize / size);
    int local_end = (rank + 1) * (matrixSize / size);

    for (int i = local_start; i < local_end; i++) {
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
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 3) {
        if (rank == 0) {
            printf("Usage: %s <matrix size> <tile size>\n", argv[0]);
        }
        MPI_Finalize();
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

    matrixVectorMul(matrix, vector, result, matrixSize, tileSize, rank, size);

    int *recvbuf = NULL;
    if (rank == 0) {
        recvbuf = (int *)malloc(matrixSize * sizeof(int));
    }

    MPI_Gather(result, matrixSize / size, MPI_INT, recvbuf, matrixSize / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Result:\n");
        for (int i = 0; i < matrixSize; i++) {
            printf("%d ", recvbuf[i]);
        }
        printf("\n");
        free(recvbuf);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < matrixSize; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);

    MPI_Finalize();

    return 0;
}
