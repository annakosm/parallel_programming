# Compiler
CC = gcc

# Executable
EXEC = omp_mat_vect_rand_split

# Arguments
ARG = 2 10000 10000

# Object files
 OBJ = omp_mat_vect_rand_split.o 
#OBJ = pi2.o my_rand.o

#EXPORT
EXA= export OMP_SCHEDULE=AUTO
EXS= export OMP_SCHEDULE=STATIC   
EXD= export OMP_SCHEDULE=DYNAMIC   
EXG= export OMP_SCHEDULE=GUIDED    
DEF= export OMP_SCHEDULE=DEFAULT

all: $(EXEC)

$(EXEC): $(OBJ)

	 $(CC) -g -Wall -fopenmp -o omp_mat_vect_rand_split omp_mat_vect_rand_split.c 
	

auto: $(EXEC)
	$(EXA)

static: $(EXEC)
	$(EXS)

dynamic: $(EXEC)
	$(EXD)

guided: $(EXEC)
	$(EXG)	 

default: $(EXEC)
	$(DEF)

run: $(EXEC) 
	./$(EXEC) $(ARG)

clean:
	rm -f $(OBJ) $(EXEC)