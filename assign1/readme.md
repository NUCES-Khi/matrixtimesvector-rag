# Assignment 1
## Team Members
Ghazanfar Adnan 21K-3115
Rija Anwar 21K-3069
Abbas Altaf 21K-3052
## Output Screenshots
![image](https://github.com/NUCES-Khi/matrixtimesvector-rag/assets/71560374/e1af3ba7-6e20-487f-a877-5fb48499a7c2)
![image](https://github.com/NUCES-Khi/matrixtimesvector-rag/assets/71560374/08b99c57-747b-48ea-88d3-6aec64f7d5e8)
![image](https://github.com/NUCES-Khi/matrixtimesvector-rag/assets/71560374/19ff826a-8a48-46a1-b1e5-9d89163406e1)

## Results and Analysis
After implementing the codes and conducting thorough evaluations, we have gained insights into the performance of various matrix-vector multiplication algorithms for different input sizes. Here's a general analysis based on our findings:

Sequential Algorithm: The sequential algorithm performs matrix-vector multiplication without any parallelization. It is suitable for small to medium-sized matrices where parallelization overhead is significant compared to computation time. However, its performance may degrade significantly for large matrices due to lack of parallelism.

OpenMP Naive Algorithm: The OpenMP naive algorithm parallelizes the computation using shared-memory multiprocessing with OpenMP directives. It demonstrates improved performance over the sequential algorithm for medium-sized matrices on multicore CPUs. However, scalability may become an issue for larger matrices due to limited parallelism and potential cache contention.

MPI Naive Algorithm: The MPI naive algorithm parallelizes the computation across distributed-memory systems using the Message Passing Interface (MPI). It offers scalability and can handle very large matrices by distributing the workload across multiple nodes. However, communication overhead may become a bottleneck for smaller matrices and on systems with high latency interconnects.

OpenMP Tiled Algorithm: The OpenMP tiled algorithm divides the matrix into smaller tiles to reduce cache contention and enhance data locality. It performs well on multicore CPUs for medium to large-sized matrices, as it maximizes cache utilization and minimizes memory access latency. However, the performance gain may plateau for very large matrices due to memory bandwidth limitations.

MPI Tiled Algorithm: The MPI tiled algorithm combines the benefits of MPI parallelization with tiling to achieve scalability across distributed-memory systems. It is suitable for very large matrices where the computation needs to be distributed across multiple nodes efficiently. However, it may exhibit higher communication overhead compared to the MPI naive algorithm due to additional data exchanges between nodes.

## Major Problems Encountered
1. Memory Allocation Errors: At the beginning of our implementation, we encountered memory allocation errors when trying to dynamically allocate memory for matrices and vectors. Some of our memory allocation calls were returning NULL, indicating that memory allocation failed.
To address this issue, we carefully reviewed our memory allocation code and added checks to ensure that memory allocation was successful.
2. Parallelization Overheads: As we parallelized our algorithms using OpenMP or MPI, we noticed that the overhead of thread/process creation and synchronization was significant. This overhead was leading to inefficient performance, particularly for smaller problem sizes.
To address this issue, we optimized our parallelization strategies by reducing synchronization points and exploiting parallelism at a coarser granularity. We also used profiling tools to identify critical sections of code and optimized them for better parallel performance.
