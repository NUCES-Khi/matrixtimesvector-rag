#!/bin/bash

# Compile C programs
gcc -o sequential_matrix_vector sequential_matrix_vector.c -lm
gcc -o openmp_naive_matrix_vector openmp_naive_matrix_vector.c -fopenmp -lm
mpicc -o mpi_naive_matrix_vector mpi_naive_matrix_vector.c -lm
gcc -o openmp_tiled_matrix_vector openmp_tiled_matrix_vector.c -fopenmp -lm
mpicc -o mpi_tiled_matrix_vector mpi_tiled_matrix_vector.c -lm

# Define input sizes
input_sizes=(64 128 256 512 1024 2048 4096 8192 16384)

# Run and time each program for different input sizes at least 10 times
echo "Matrix Size,Sequential,OpenMP_Naive,MPI_Naive,OpenMP_Tiled,MPI_Tiled"
for size in "${input_sizes[@]}"
do
    sequential_sum=0
    openmp_naive_sum=0
    mpi_naive_sum=0
    openmp_tiled_sum=0
    mpi_tiled_sum=0

    echo -n "$size,"
    for ((i=1; i<=10; i++))
    do
        sequential_time=$( { time -p ./sequential_matrix_vector $size $size; } 2>&1 | grep real | awk '{print $2}' )
        sequential_sum=$( awk "BEGIN {print $sequential_sum + $sequential_time}" )

        openmp_naive_time=$( { time -p ./openmp_naive_matrix_vector $size $size; } 2>&1 | grep real | awk '{print $2}' )
        openmp_naive_sum=$( awk "BEGIN {print $openmp_naive_sum + $openmp_naive_time}" )

        mpi_naive_time=$( { time -p mpirun -np 4 ./mpi_naive_matrix_vector $size $size; } 2>&1 | grep real | awk '{print $2}' )
        mpi_naive_sum=$( awk "BEGIN {print $mpi_naive_sum + $mpi_naive_time}" )

        openmp_tiled_time=$( { time -p ./openmp_tiled_matrix_vector $size $size; } 2>&1 | grep real | awk '{print $2}' )
        openmp_tiled_sum=$( awk "BEGIN {print $openmp_tiled_sum + $openmp_tiled_time}" )

        mpi_tiled_time=$( { time -p mpirun -np 4 ./mpi_tiled_matrix_vector $size $size; } 2>&1 | grep real | awk '{print $2}' )
        mpi_tiled_sum=$( awk "BEGIN {print $mpi_tiled_sum + $mpi_tiled_time}" )
    done

    sequential_avg=$( awk "BEGIN {print $sequential_sum / 10}" )
    openmp_naive_avg=$( awk "BEGIN {print $openmp_naive_sum / 10}" )
    mpi_naive_avg=$( awk "BEGIN {print $mpi_naive_sum / 10}" )
    openmp_tiled_avg=$( awk "BEGIN {print $openmp_tiled_sum / 10}" )
    mpi_tiled_avg=$( awk "BEGIN {print $mpi_tiled_sum / 10}" )

    echo "$sequential_avg,$openmp_naive_avg,$mpi_naive_avg,$openmp_tiled_avg,$mpi_tiled_avg"
done
