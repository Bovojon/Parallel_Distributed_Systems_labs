#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> 
#include <time.h>

int main(int argc, char *argv[]){
    int i, sum, comm_sz, my_rank, local_n, total_int, local_sum;
    int N = atoi(argv[1]);    
    // Initialize MPI
    MPI_Init(&argc, &argv);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    // Determine rank of process
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    local_n = N/comm_sz;    
    srand(time(NULL));
    sum = 0;
    for (i= 0; i < local_n; i++) {
        sum += rand() %10;
    }
    local_sum = sum;
    printf("Process %d calculated sum %d\n", my_rank, sum); 
    // Use MPI_Reduce which is more efficient than MPI_Send and MPI_Recv
    MPI_Reduce(&local_sum, &total_int, 1, MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
    
    if (my_rank ==0){
        printf("The final sum is %d\n", total_int);
    }
    // Finalize
    MPI_Finalize();
    return 0;
}