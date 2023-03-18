This version uses openMP parallelization to estimate pi using the monte carlo method . The results can be obtained using the python 3 script script1.py, the which performs two processes.To compare the pi_serial.c and pi_reduce.c programs, we notice that the
program pi_reduce.c has worse execution time, while average execution times
it's about:
Average time for program pi_serial.c = 0.20196416666666664
Average time for program pi_reduce.c = 0.8816914166666665
This is because the parallel approach for small numbers performs worse
from the serial, while when the value of total becomes large enough we have the opposite
result.

RUN SCRIPT : pyhton3 script script1.py