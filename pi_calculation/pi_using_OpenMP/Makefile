# Compiler
CC = gcc

# Executable
EXEC = pi

# Arguments
ARG = 4 80000

# Object files
OBJ = pi.o my_rand.o

all: $(EXEC)

$(EXEC): $(OBJ)

	$(CC) -g -Wall -fopenmp -o pi pi.c my_rand.c


run: $(EXEC) 
	./$(EXEC) $(ARG)

clean:
	rm -f $(OBJ) $(EXEC)