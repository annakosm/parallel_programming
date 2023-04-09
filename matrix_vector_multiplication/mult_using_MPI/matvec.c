/* File:     matvec.c
 * Εργασία 3 – Προγραμματισμός με MPI
 * Άσκηση 3.1
 
 * Compile:  mpicc -g -Wall -o matvec matvec.c 
 * 
 * Run:      mpiexec -n <number of processes> ./matvec <n>
 *      
 * Python chript:   type in terminal: python3 script2.py	
 * 
 * Purpose:     This program multiplies an array A  
 *              with a vector x, using Parallel 
 *              Programming with MPI.
 * 
 * Output:   A vector that is the result of multiplication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "timer.h"

double* Generate_matrix(int n);
double* Generate_vector(int n);
void partition_A(double* A, double* local_A, int n, int rank, int local_n);
void Print_matrix(double* A, int lines, int cols, int rank);
void Mat_vect_mult(double local_A[], double local_x[], 
                double local_y[], int n, int local_n, MPI_Comm comm);

int main(int argc, char* argv[]) {
    double* local_A;
    double* local_x;
    double* local_y;
    double* A;
    double* x = NULL;
    double* y;
    int n, local_n;
    int my_rank, comm_sz;
    double start, finish, estimate_time;
    
    GET_TIME(start);

    MPI_Comm comm;

    MPI_Init(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    n = atoi(argv[1]);
    local_n = n / comm_sz;
    local_A = malloc(n*local_n*sizeof(double));
    local_x = malloc(local_n*sizeof(double));
    local_y = malloc(n*sizeof(double));
    srand(my_rank);

    /* Process 0 */ 
    if (my_rank == 0) {
        y =  malloc(n*sizeof(double));
        A = Generate_matrix(n);
        x = Generate_vector(n);
        // Print_matrix(A, n, n, my_rank);
        for (int rank = 1; rank < comm_sz; rank++) {
            partition_A(A, local_A, n, rank, local_n);
            MPI_Send(local_A, n*local_n, MPI_DOUBLE, rank, 0, comm);
        }
        partition_A(A, local_A, n, 0, local_n);

        MPI_Scatter(x, local_n, MPI_DOUBLE, local_x, local_n, MPI_DOUBLE, 0, comm);
        
    }
    /* Other processes */ 
    else {
        MPI_Recv(local_A, n*local_n, MPI_DOUBLE, 0, 0, comm, MPI_STATUS_IGNORE);
        MPI_Scatter(x, local_n, MPI_DOUBLE, local_x, local_n, MPI_DOUBLE, 0, comm);
       
    }
    
    /* All processes must arrive there */ 
    MPI_Barrier(comm);
    Mat_vect_mult(local_A, local_x, local_y, n, local_n, comm ); 

    MPI_Reduce(local_y, y, n, MPI_DOUBLE, MPI_SUM, 0, comm);
    
    if (my_rank == 0) {
        /* Print time */
        GET_TIME(finish);
        estimate_time = (double)(finish - start);

        printf(" TIME = %f\n", estimate_time);

        /* Print final vector */
        for(int i=0; i<n; i++){
            printf("y[%d] = %f\n",i, y[i]);
        }

        free(A);
        free(x);
        free(y);
    }

    free(local_A);
    free(local_x);
    free(local_y);

    MPI_Finalize();
}


double* Generate_matrix(int n) {

    double *A = malloc(n*n*sizeof(double));

    for (int i = 0; i <n ; i++){
        for (int j = 0; j < n; j++){
            A[i*n + j] = ((double) random())/((double) RAND_MAX);
            
        }
    }
    return A;

}  /* Generate_matrix */

double* Generate_vector(int n) {

    double* x = malloc(n*sizeof(double));

    for (int i = 0; i < n; i++){
        x[i] = ((double) rand())/((double) RAND_MAX);
        // printf("generate vector x = %f \n",x[i]);

    }

    return x;
}  /* Generate_vector */


void partition_A(double* A, double* local_A, int n, int rank, int local_n) {
    int pos = 0;
  
    for (int i = 0; i < n; i++) {
        for (int j = rank*local_n; j < (rank+1)*local_n; j++) {
            local_A[pos] = A[j + i*n];
            //printf("local A= %f\n",local_A[pos] );
            pos++;
        }
    }
    
}

void Print_matrix(double* A, int lines, int cols, int rank) {
    
    // printf("rank = %d\n", rank);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            // printf("%f ", A[i*lines+j]);
        }
        // printf("\n");
    }
}

void Mat_vect_mult(double *local_A , double *local_x , double *local_y,
             int n ,int local_n , MPI_Comm comm ) {



    for (int i = 0; i < n; i++) {
        local_y[i] = 0.0;
        for (int j = 0; j < local_n; j++){
            local_y[i] += local_A[i*local_n+j]*local_x[j];
           // printf("local_A = %f\n", local_A[i*local_n+j]);

        }
        // printf("local_y = %f\n", local_y[i]);

    }
}  /* Mat_vect_mult */
