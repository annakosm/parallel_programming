 /* File:     pi_serial.c
 * Εργασία 3 – Προγραμματισμός με MPI
 * Άσκηση 3.1
 * sdi2000093 Άννα Κοσμίδη
 * sdi2000107 Λυδία Κυριάκου
 *
 * Compile:  gcc -o pi_serial pi_serial.c 
 * 
 * Run:      ./pi_serial <n>
 *           n is the number of terms of the series to use. 
 *   
 * Python chript: type in terminal: python3 script1.py       
 *  
 * Output:   Estimate of pi.
 */     

#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double Serial_pi(long long n);

int main(int argc, char* argv[]) {
   double start, finish, estimate_time;
   double sum = 0.0;

   GET_TIME(start)

   /* Get and check argument */
   int n = strtoll(argv[1], NULL, 10);
   if (argc != 2) {
      printf("Too many arguments");
   }
   if (n <= 0) {
      printf("n should be > 0 \n");
   }

   /* Call Serial function to calculate pi */
   sum = Serial_pi(n);
   GET_TIME(finish)
   estimate_time = (double)(finish - start);
        
   printf("%.15f\n", sum);
   printf("%f\n", estimate_time);

   return 0;
}  /* main */


/*------------------------------------------------------------------
 * Function:   Serial_pi
 * Purpose:    Estimate pi
 * In arg:     n
 * Return val: Estimate of pi using n terms of Maclaurin series
 */
double Serial_pi(long long n) {
   double sum = 0.0;
   long long i;
   double factor = 1.0;

   for (i = 0; i < n; i++, factor = -factor) {
      sum += factor/(2*i+1);
   }
   return 4.0*sum;

}  /* Serial_pi */

