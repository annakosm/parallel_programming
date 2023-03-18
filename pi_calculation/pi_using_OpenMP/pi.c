/* Εργασία 2 – Προγραμματισμός με OpenMP
 * Άσκηση 2.1
 * sdi2000093 Άννα Κοσμίδη
 * sdi2000107 Λυδία Κυριάκου
 * File:     
 *      pi.c 
 * Compile:  
 *      gcc -g -Wall -fopenmp -o pi pi.c my_rand.c 
 * Run:
 *      ./pi <thread_count> <total>
 * Makefile:
 *      make --> for compilation
 *      make run --> for execution
 * Python chript:
 * 		type in terminal: python3 script1.py
 * Purpose:
 *      This program calculates the number π with 
 *      the 'Monte Carlo' method, using Parallel 
 *      Programming with OpenMP. This version uses 
 *      a parallel for directive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <omp.h>

#include "timer.h"
#include "my_rand.h"

/* global const */ 
const int MAX_THREADS = 1024;

/* Serial functions */
void Usage(char* prog_name);
double Serial(long long int total);

/* Parallel function */
double Thread_sum(int thread_count, long long int total);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]){
    /* Variables */
    double estimate_p;
    int thread_count;
    double start, finish, elapsed;
    long long int arrow_circle, total;

    /* Get arguments */
    thread_count = strtol(argv[1], NULL, 10);  
    if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
    total = strtoll(argv[2], NULL, 10);
    if (total<= 0) Usage(argv[0]);

    estimate_p = 0.0;
    arrow_circle = 0;

    /* Get time */
    GET_TIME(start);
    arrow_circle = Thread_sum(thread_count, total);
    GET_TIME(finish);
    elapsed = finish - start;

    estimate_p = 4*arrow_circle/((double)total);

    printf("%f\n",estimate_p);
    printf("%e\n", elapsed);

    return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   print a message showing what the command line  
 *            should be, and terminate
 * In arg :   prog_name
 */
void Usage(char* prog_name) {
    fprintf(stderr, "usage: %s <number of threads> <total>\n", prog_name);
    fprintf(stderr, "  total is the number of throws >= 1\n");
    exit(0);
}  /* Usage */


/*------------------------------------------------------------------
 * Function:  Thread_sum
 * Purpose:   calculates the number π with the 'Monte Carlo' method,
 *            using Parallel Programming with OpenMP. 
 *            This version uses a parallel for directive.
 * In arg :   thread_count, total
 */
double Thread_sum(int thread_count, long long int total) {
    /* Variables */
    double dist2 = 0;
    unsigned seed = 1;
    double x, y;
    long long int my_arrow = 0; 
    long long int i;

#   pragma omp parallel for num_threads(thread_count) \
        reduction(+: my_arrow)
    for( i=0; i<total; i++){
        /* We want x, y between (-1,1) */
        x = 2.0*my_drand(&seed)-1.0;
        y = 2.0*my_drand(&seed)-1.0;
        dist2 = x*x+y*y;
        if(dist2 <= 1){
            my_arrow++;  
        }
    }

    return my_arrow;
}  /* Thread_sum */


