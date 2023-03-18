# Compiler
CC = gcc

# Executable
EXEC = ask1_1Parallel

# Arguments
ARG = 2 80000

# Object files
OBJ = ask1_1Parallel.o my_rand.o

all: $(EXEC)

$(EXEC): $(OBJ)

	$(CC) -g -Wall -o ask1_1Parallel ask1_1Parallel.c my_rand.c -lm -lpthread

run: $(EXEC) 
	./$(EXEC) $(ARG)

clean:
	rm -f $(OBJ) $(EXEC)