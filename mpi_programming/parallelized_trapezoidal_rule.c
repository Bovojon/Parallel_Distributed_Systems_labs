#include <stdio.h>
#include <mpi.h> 
#include <string.h>
#include <stdlib.h>
#include "functions_five.h"
    
double Trap(double left_endpoint, double right_endpoint, int trap_count, double base_len, int N) {
    double estimate, x;
    int i;
    if (N == 1){
        estimate = (f(left_endpoint)+f(right_endpoint))/2.0;
        for (i=1; i<=trap_count-1; i++) {
            x = left_endpoint + i*base_len;
            estimate += f(x);
        }
    }
    else if (N == 2) {
        estimate = (g(left_endpoint)+g(right_endpoint))/2.0;
        for (i=1; i<=trap_count-1; i++) {
            x = left_endpoint + i*base_len;
            estimate += g(x);
        }
    }
    else if (N == 3) {
        estimate = (h(left_endpoint)+h(right_endpoint))/2.0;
        for (i=1; i<=trap_count-1; i++) {
            x = left_endpoint + i*base_len;
            estimate += h(x);
        }
    }
    else if (N == 4) {
        estimate = (k(left_endpoint)+k(right_endpoint))/2.0;
        for (i=1; i<=trap_count-1; i++) {
            x = left_endpoint + i*base_len;
            estimate += k(x);
        }
    }
    else{
        estimate = (j(left_endpoint)+j(right_endpoint))/2.0;
        for (i=1; i<=trap_count-1; i++) {
            x = left_endpoint + i*base_len;
            estimate += j(x);
        }
    }
    estimate = estimate*base_len;
    return estimate;
}

int main(int argc, char *argv[]) {
    int my_rank, comm_sz, local_n;
    double h, local_a, local_b;
    double local_int, total_int;
    int N = atoi(argv[1]);
    int n = atoi(argv[2]);
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    /*
    1 for f
    2 for g
    3 for h
    4 for k
    5 for j
    */
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    h=(b-a)/n;
    local_n = n/comm_sz;
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    local_int = Trap(local_a, local_b, local_n, h, N);
    
    MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (my_rank == 0){
        printf("Given n = %d trapezoids, the estimated the integral from a = %f to b = %f using Trap rule is %.6e\n", n, a, b, total_int);
    } 
    MPI_Finalize();
    return 0;
}