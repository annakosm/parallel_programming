# Εργασία 2 – Προγραμματισμός με OpenMP
# Άσκηση 2.1
# sdi2000093 Άννα Κοσμίδη
# sdi2000107 Λυδία Κυριάκου
# This python 3 script compiles and run 
# the c program pi.c 
  
import subprocess

def excuteC():
  
    subprocess.check_call("gcc -g -Wall -fopenmp -o pi pi.c my_rand.c;", shell = True)

    pi_list = []
    time_list = []
    sum_pi = []
    sum_time = []

    # Run pi.c 4 times
    for i in range(1, 5):
        print("*************** ", i," ***************")

        # For total = 10000000
        total = 10000000
        b = str(total)
        # For 2, 3, 4, 6 and 8 threads
        for threads in range(2, 10, 2):
            print("--------------------")
            print("total: ", total)
            print("threads: ", threads)
            a = str(threads)
            exe = "./pi " + a + " " + b
            
            output = subprocess.check_output(exe, shell=True)
            mytuple = output.split()

            pi_cast = float(mytuple[0])
            time_cast = float(mytuple[1])

            print("pi = ",pi_cast)
            print("time = ",time_cast)
            
            pi_list.append(pi_cast)
            time_list.append(time_cast)

            sum_pi.append(pi_cast)
            sum_time.append(time_cast)
        
        # For total = 10000000
        total = 100000000
        b = str(total)
        # For 2, 3, 4, 6 and 8 threads
        for threads in range(2, 10, 2):
            print("--------------------")
            print("total: ", total)
            print("threads: ", threads)
            a = str(threads)
            exe = "./pi " + a + " " + b
            
            output = subprocess.check_output(exe, shell=True)
            mytuple = output.split()

            pi_cast = float(mytuple[0])
            time_cast = float(mytuple[1])
            print("pi = ", pi_cast)
            print("time = ", time_cast)
            
            pi_list.append(pi_cast)
            time_list.append(time_cast)

            sum_pi.append(pi_cast)
            sum_time.append(time_cast)
       
            
    print("Average estimate p = ", sum(sum_pi)/len(sum_pi))
    print("Average time = ", sum(sum_time)/len(sum_time))

    pi_list = []
    time_list = []
    sum_pi = []
    sum_time = []

    # συγκριση με ασκ. 1.1
    for total in range(100000000, 1500000000, 700000000):
        b = str(total)
        # For 2, 3, 4, 6 and 8 threads
        for threads in range(2, 10, 2):
            a = str(threads)
            exe = "./pi " + a + " " + b
            print(exe)
            
            output = subprocess.check_output(exe, shell=True)
            mytuple = output.split()

            pi_cast = float(mytuple[0])
            print(pi_cast)
            time_cast = float(mytuple[1])
            print(time_cast)
            
            pi_list.append(pi_cast)
            time_list.append(time_cast)
            sum_pi.append(pi_cast)
            sum_time.append(time_cast)


    print("Average estimate p = ", sum(sum_pi)/len(sum_pi))
    print("Average time = ", sum(sum_time)/len(sum_time))

  
# Driver function
if __name__=="__main__":
    excuteC() 