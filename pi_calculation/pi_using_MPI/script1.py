# Εργασία 3 – Προγραμματισμός με OpenMP
# Άσκηση 3.1
# sdi2000093 Άννα Κοσμίδη
# sdi2000107 Λυδία Κυριάκου
# This python 3 script compiles and run 
# the c programs pi.c, pi_reduce.c, pi_serial.c
# python3 script1.py
  
import subprocess
   
def excute_pi_serial_pi_reduce():
    
    pi_list = []
    time_list = []
    sum_pi = []
    sum_time = []

    #  run pi_serial.c

    print("pi_serial.c")
    print("------------")
    subprocess.check_call("gcc -o pi_serial pi_serial.c;", shell = True)
    
    pi_list = []
    time_list = []
    sum_pi = []
    sum_time = []
    
    for i in range(1, 4):
        print("*************** ",i," ***************")
        # For total = 10 ^ 8
        total = 8000000
        b = str(total)
        print("--------------------")
        print("total: ", total)
        exe = "./pi_serial " + b

        output = subprocess.check_output(exe, shell=True)
        mytuple = output.split()

        pi_cast = float(mytuple[0])
        time_cast = float(mytuple[1])

        print("pi serial = ",pi_cast)
        print("time serial = ",time_cast)

        pi_list.append(pi_cast)
        time_list.append(time_cast)

        sum_pi.append(pi_cast)
        sum_time.append(time_cast)
    
        # For total = 10 ^ 9
        total = 80000000
        b = str(total)
        print("--------------------")
        print("total: ", total)
        exe = "./pi_serial " + b
        
        output = subprocess.check_output(exe, shell=True)
        mytuple = output.split()

        pi_cast = float(mytuple[0])
        time_cast = float(mytuple[1])
        print("pi serial = ", pi_cast)
        print("time serial = ", time_cast)
        
        pi_list.append(pi_cast)
        time_list.append(time_cast)

        sum_pi.append(pi_cast)
        sum_time.append(time_cast)
       
    
    av_p_p = sum(sum_pi)/len(sum_pi)
    av_time_p = sum(sum_time)/len(sum_time)
    print("Average estimate p with pi_serial.c = ", av_p_p)
    print("Average time with pi_serial.c = ", av_time_p)
    
    print("\n--------------------------------------------------------------------------\n")
    
    
    # run pi_reduce.c
    print("pi_reduce.c")
    print("------------")
    subprocess.check_call("mpicc -g -Wall -o pi_reduce pi_reduce.c my_rand.c;", shell = True)    
    
    
    
    
    for i in range(1, 4):
        print("*************** ",i," ***************")
        
        # set n
        total = 8000000
        b = str(total)
        
        i_while = 5
        processes=1
        while(i_while):
            print("--------------------")
            print("total: ", total)
            print("processes: ", processes)
            a = str(processes)
            exe = "mpiexec -n " + a + " ./pi_reduce " + b
        
            output = subprocess.check_output(exe, shell=True)
            mytuple = output.split()

            pi_cast = float(mytuple[0])
            time_cast = float(mytuple[1])

            print("pi reduce = ",pi_cast)
            print("time reduce = ",time_cast)
            
            pi_list.append(pi_cast)
            time_list.append(time_cast)

            sum_pi.append(pi_cast)
            sum_time.append(time_cast)
                
                
            processes*=2
            i_while-=1
            
        # set n
        total = 80000000
        b = str(total)
        
        i_while = 5
        processes=1
        while(i_while):
            print("--------------------")
            print("total: ", total)
            print("processes: ", processes)
            a = str(processes)
            exe = "mpiexec -n " + a + " ./pi_reduce " + b
        
            output = subprocess.check_output(exe, shell=True)
            mytuple = output.split()

            pi_cast = float(mytuple[0])
            time_cast = float(mytuple[1])

            print("pi reduce = ",pi_cast)
            print("time reduce = ",time_cast)
            
            pi_list.append(pi_cast)
            time_list.append(time_cast)

            sum_pi.append(pi_cast)
            sum_time.append(time_cast)
                
                
            processes*=2
            i_while-=1
            
            
    av_p_p1 = sum(sum_pi)/len(sum_pi)
    av_time_p1 = sum(sum_time)/len(sum_time)
    print("Average estimate p with pi_reduce.c = ", av_p_p1)
    print("Average time with pi_reduce.c = ", av_time_p1)
            
    print("\n--------------------------------------------------------------------------\n")
    
    # conclusion
    print("\n--------------------------------------------------------------------------\n")
    print("Average time for program pi_serial.c = ", av_time_p)
    print("Average time for program pi_reduce.c = ", av_time_p1)
    S = av_time_p / av_time_p1 
    print("Acceleration = ", S)
    
    
  
# Driver function
if __name__=="__main__":
    ask = input('See results for pi_serial.c and pi_reduce.c [y,n]?\n')
    if (ask == "y"):
        excute_pi_serial_pi_reduce() 