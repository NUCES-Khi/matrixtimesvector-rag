#!/bin/bash

# Compile C programs
gcc -o sequential_matrix_vector sequential_matrix_vector.c -lm
gcc -o openmp_naive_matrix_vector openmp_naive_matrix_vector.c -fopenmp -lm
mpicc -o mpi_naive_matrix_vector mpi_naive_matrix_vector.c -lm
gcc -o openmp_tiled_matrix_vector openmp_tiled_matrix_vector.c -fopenmp -lm
mpicc -o mpi_tiled_matrix_vector mpi_tiled_matrix_vector.c -lm

# Define input sizes
input_sizes=(64 128 256 512 1024 2048 4096 8192 16384)

# Run and time each program for different input sizes
for size in "${input_sizes[@]}"
do
    echo "Input Size: $size"

    # Sequential Matrix-Vector Multiplication
    echo -n "Sequential: "
    { time ./sequential_matrix_vector $size $size; } 2>&1 | grep real

    # OpenMP Naive Matrix-Vector Multiplication
    echo -n "OpenMP Naive: "
    { time ./openmp_naive_matrix_vector $size $size; } 2>&1 | grep real

    # MPI Naive Matrix-Vector Multiplication
    echo -n "MPI Naive: "
    { time mpirun -np 4 ./mpi_naive_matrix_vector $size $size; } 2>&1 | grep real

    # OpenMP Tiled Matrix-Vector Multiplication
    echo -n "OpenMP Tiled: "
    { time ./openmp_tiled_matrix_vector $size $size; } 2>&1 | grep real

    # MPI Tiled Matrix-Vector Multiplication
    echo -n "MPI Tiled: "
    { time mpirun -np 4 ./mpi_tiled_matrix_vector $size $size; } 2>&1 | grep real

    echo "---------------------------------------"
done
