/* sdi2000093 Άννα Κοσμίδη
 * sdi2000107 Λυδία Κυριάκου
 * File:     
 *     ask1_2b.c 
 *
 * Compile:  
 *    gcc -g -Wall -o ask1_2b ask1_2b.c -lpthread
 * Usage:
 *     ask1_2b <thread_count> <m> <n>
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

/* Global variables */
int     thread_count;
int     m, n;
double* A;
double* x;
double* y;

/* Serial functions */
void Usage(char* prog_name);
void Gen_matrix(double A[], int m, int n);
void Read_matrix(char* prompt, double A[], int m, int n);
void Gen_vector(double x[], int n);
void Read_vector(char* prompt, double x[], int n);
void Print_matrix(char* title, double A[], int m, int n);
void Print_vector(char* title, double y[], double m);

/* Parallel function */
void *Pth_mat_vect(void* rank);

/*------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles;

   if (argc != 4) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   m = strtol(argv[2], NULL, 10);
   n = strtol(argv[3], NULL, 10);

#  ifdef DEBUG
   printf("thread_count =  %d, m = %d, n = %d\n", thread_count, m, n);
#  endif

   thread_handles = malloc(thread_count*sizeof(pthread_t));
   A = malloc(m*n*sizeof(double));
   x = malloc(n*sizeof(double));
   y = malloc(m*sizeof(double));
   
   Gen_matrix(A, m, n);
#  ifdef DEBUG
   Print_matrix("We generated", A, m, n); 
#  endif

   Gen_vector(x, n);
#  ifdef DEBUG
   Print_vector("We generated", x, n); 
#  endif

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
         Pth_mat_vect, (void*) thread);

   for (thread = 0; thread < thread_count; thread++)
      pthread_join(thread_handles[thread], NULL);

#  ifdef DEBUG
   Print_vector("The product is", y, m); 
#  endif

   free(A);
   free(x);
   free(y);

   return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   print a message showing what the command line should
 *            be, and terminate
 * In arg :   prog_name
 */
void Usage (char* prog_name) {
   fprintf(stderr, "usage: %s <thread_count> <m> <n>\n", prog_name);
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    Read_matrix
 * Purpose:     Read in the matrix
 * In args:     prompt, m, n
 * Out arg:     A
 */
void Read_matrix(char* prompt, double A[], int m, int n) {
   int             i, j;

   printf("%s\n", prompt);
   for (i = 0; i < m; i++) 
      for (j = 0; j < n; j++)
         scanf("%lf", &A[i*n+j]);
}  /* Read_matrix */

/*------------------------------------------------------------------
 * Function: Gen_matrix
 * Purpose:  Use the random number generator random to generate
 *    the entries in A
 * In args:  m, n
 * Out arg:  A
 */
void Gen_matrix(double A[], int m, int n) {
   int i, j;
   for (i = 0; i < m; i++)
      for (j = 0; j < n; j++)
         A[i*n+j] = random()/((double) RAND_MAX);
}  /* Gen_matrix */

/*------------------------------------------------------------------
 * Function: Gen_vector
 * Purpose:  Use the random number generator random to generate
 *    the entries in x
 * In arg:   n
 * Out arg:  A
 */
void Gen_vector(double x[], int n) {
   int i;
   for (i = 0; i < n; i++)
      x[i] = random()/((double) RAND_MAX);
}  /* Gen_vector */

/*------------------------------------------------------------------
 * Function:        Read_vector
 * Purpose:         Read in the vector x
 * In arg:          prompt, n
 * Out arg:         x
 */
void Read_vector(char* prompt, double x[], int n) {
   int   i;

   printf("%s\n", prompt);
   for (i = 0; i < n; i++) 
      scanf("%lf", &x[i]);
}  /* Read_vector */

/*------------------------------------------------------------------
 * Function:       Pth_mat_vect
 * Purpose:        Multiply an mxn matrix by an nx1 column vector
 * In arg:         rank
 * Global in vars: A, x, m, n, thread_count
 * Global out var: y
 */
void *Pth_mat_vect(void* rank) {
   long my_rank = (long) rank;
   int i, j; 
   int local_m = m/thread_count; 
   int my_first_row = my_rank*local_m;
   int my_last_row = my_first_row + local_m;
   register int sub = my_first_row*n;
   double start, finish;
   double temp;

#  ifdef DEBUG
   printf("Thread %ld > local_m = %d, sub = %d\n",
         my_rank, local_m, sub);
#  endif

   int mine;
   GET_TIME(start);
   for (i = my_first_row; i < my_last_row; i++) {
      mine = 0.0;
      for (j = 0; j < n; j++) {
          temp = A[sub++];
          temp *= x[j];
          mine += temp;
      }
      y[i] = mine;
   }
   GET_TIME(finish);
   printf("Thread %ld > Elapsed time = %e seconds\n", 
      my_rank, finish - start);

   return NULL;
}  /* Pth_mat_vect */


/*------------------------------------------------------------------
 * Function:    Print_matrix
 * Purpose:     Print the matrix
 * In args:     title, A, m, n
 */
void Print_matrix( char* title, double A[], int m, int n) {
   int   i, j;

   printf("%s\n", title);
   for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
         printf("%6.3f ", A[i*n + j]);
      printf("\n");
   }
}  /* Print_matrix */


/*------------------------------------------------------------------
 * Function:    Print_vector
 * Purpose:     Print a vector
 * In args:     title, y, m
 */
void Print_vector(char* title, double y[], double m) {
   int   i;

   printf("%s\n", title);
   for (i = 0; i < m; i++)
      printf("%6.3f ", y[i]);
   printf("\n");
}  /* Print_vector */

  
