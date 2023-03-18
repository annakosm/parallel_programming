In this exercise you are asked to evaluate and deal with the problem of false sharing. Your
given the matrix-vector multiplication program of the book “Introduction to Parallel
Programming". You are asked to modify the matrix-vector multiplication program when there is a possibility of false sharing following the following two approaches:

1. In the first approach you fill in the vector y with dummy elements. Completion must be done with in such a way that, if the threads are running in lock step, there is no possibility a cache line containing an element of y to be accessed by two or more threads.

2.In the second approach modify the matrix-vector multiplication program so that each thread
uses private storage for its own part of y in the for i loop. When a thread terminates
computing its own part of y, it should copy its local data to the shared one
variable.