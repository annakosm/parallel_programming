/* sdi2000093 Άννα Κοσμίδη
 * sdi2000107 Λυδία Κυριάκου
 * File:     
 *     pth_mat_vect_rand_split.c 
 * Compile:  
 *    gcc -g -Wall -o ask1_1Parallel ask1_1Parallel.c my_rand.c -lm -lpthread
 * Usage:
 *    ask1_1Parallel <thread_count> <total>
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"
#include "my_rand.h"

/* global const */ 
const int MAX_THREADS = 1024;

/* Global variables */
long thread_count;
double estimate_p;
long long int arrow_circle,total;
pthread_mutex_t mutex;
double x,y;

/* Serial functions */
void Usage(char* prog_name);
void Get_args(int argc, char* argv[]);
double Serial(long long int total);

/* Parallel function */
void* Thread_sum(void* rank);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]){
    long thread;
    pthread_t* thread_handles;
    double start, finish,elapsed;
    arrow_circle=0;
    /* Get arguments */
    Get_args(argc, argv);

    /* Get the number of threads */
    thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t)); 
    pthread_mutex_init(&mutex, NULL);

    estimate_p = 0.0;

    GET_TIME(start);
    for (thread = 0; thread < thread_count; thread++)  
            pthread_create(&thread_handles[thread], NULL,Thread_sum, (void*)thread);  

        for (thread = 0; thread < thread_count; thread++) 
        pthread_join(thread_handles[thread], NULL); 
    GET_TIME(finish);
    elapsed = finish - start;

    estimate_p=4*arrow_circle/((double)total); 
    printf("--------------------------------------------\n");
    printf("Parallel\n");
    printf("With total = %lld terms,\n", total);
    printf("   Our estimate of estimate_p = %f\n", estimate_p);
    printf("The elapsed time is %e seconds\n", elapsed);
    printf("--------------------------------------------\n");

    GET_TIME(start);
    estimate_p = Serial(total);
    GET_TIME(finish);
    elapsed = finish - start;
    printf("--------------------------------------------\n");
    printf("Serial\n");
    printf("   Single thread est  = %f\n", estimate_p);
    printf("The elapsed time is %e seconds\n", elapsed);
    printf("--------------------------------------------\n");
    
    pthread_mutex_destroy(&mutex);
    free(thread_handles);
    return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:  Usage
 */
void Usage(char* prog_name) {
    fprintf(stderr, "usage: %s <number of threads> <total>\n", prog_name);
    fprintf(stderr, "  total is the number of throws >= 1\n");
    exit(0);
}  /* Usage */


/*------------------------------------------------------------------
 * Function:  Get_args
 */
void Get_args(int argc, char* argv[]) {
    if (argc != 3) Usage(argv[0]);
    thread_count = strtol(argv[1], NULL, 10);  
    if (thread_count <= 0 || thread_count > MAX_THREADS) Usage(argv[0]);
    total = strtoll(argv[2], NULL, 10);
    if (total<= 0) Usage(argv[0]);
}  /* Usage */


/*------------------------------------------------------------------
 * Function:  Thread_sum
 */
void* Thread_sum(void* rank) {
    long my_rank = (long) rank;
    long long my_n = total/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    double dist2 = 0;
    unsigned seed = 1;
    double x, y;
    long long int my_arrow = 0; 
    long long int i;

    for( i=my_first_i; i<my_last_i; i++){
        /* We want x, y between (-1,1) */
        x = 2.0*my_drand(&seed)-1.0;
        y = 2.0*my_drand(&seed)-1.0;
        dist2 = x*x+y*y;
        if(dist2 <= 1){
            my_arrow++;  
        }
    }
    pthread_mutex_lock(&mutex);
    arrow_circle += my_arrow;
    pthread_mutex_unlock(&mutex);

    return NULL;
}  /* Thread_sum */


/*------------------------------------------------------------------
 * Function:  Serial
 */
double Serial(long long int total){
    long long int arrow_circle = 0;
    double dist2;
    double estimate;
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

    estimate = (4*arrow_circle/((double)total));
    return estimate;
}  /* Serial */