/* File:     pi_reduce.c
 * Εργασία 3 – Προγραμματισμός με MPI
 * Άσκηση 3.1
 * sdi2000093 Άννα Κοσμίδη
 * sdi2000107 Λυδία Κυριάκου
 * 
 * Compile:  mpicc -g -Wall -o pi_reduce pi_reduce.c my_rand.c
 * 
 * Run:      mpiexec -n <number of processes> ./pi_reduce <total>
 *     
 * Python chript:   type in terminal: python3 script1.py	
 * 
 * Purpose:     This program calculates the number π with 
 *              the 'Monte Carlo' method, using Parallel 
 *              Programming with MPI.
 * 
 * Output:   Estimate of pi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#include "timer.h"
#include "my_rand.h"

/* Serial functions */
long long int Arrow_sum(long long int total);

/*------------------------------------------------------------------*/
int main(int argc, char *argv[]){
    /* Variables */
    int my_rank, comm_sz;
    double estimate_p;
    double start, finish, estimate_time;
    long long int total, local_total;
    double local_int, total_int;


    estimate_p = 0.0;

    GET_TIME(start);

    /* Let the system do what it needs to start up MPI */
    MPI_Init(&argc, &argv);

    /* Get my process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out how many processes are being used */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Get and check argument */
    total = strtoll(argv[1], NULL, 10);
    if (argc != 2) {
        printf("Too many arguments");
    }
    if (total <= 0) {
        printf("n should be > 0 \n");
    }
    
    local_total = total / comm_sz;
    local_int = Arrow_sum(local_total);

    /* Add up the integrals calculated by each process */
    MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    /* Print the result */
    if (my_rank == 0) {
        estimate_p = 4*total_int/((double)total);
        /* Get time */
        GET_TIME(finish);
        estimate_time = (double)(finish - start);
        printf("%f\n", estimate_p);
        printf("%f\n", estimate_time);
    }

    /* Shut down MPI */
    MPI_Finalize();
    
    return 0;
}  /* main */



/*------------------------------------------------------------------
 * Function:  Arrow_sum
 */
long long int Arrow_sum(long long int total){
    long long int arrow_circle = 0;
    double dist2;
    unsigned seed = 1;
    long long int i;
    double x, y;

    for( i=0; i<total; i++ ){
        /* We want x, y between (-1,1) */
        x=2.0*my_drand(&seed)-1.0;
        y=2.0*my_drand(&seed)-1.0;
        dist2=x*x+y*y;
        if(dist2<=1){
            arrow_circle++;
        }
    }

    return arrow_circle;
}  /* Serial */
