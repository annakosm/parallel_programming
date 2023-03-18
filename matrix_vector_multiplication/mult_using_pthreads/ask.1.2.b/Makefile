# Compiler
CC = gcc

# Executable
EXEC = ask1_2b

# Arguments
ARG = 4 3 3

# Object files
OBJ = ask1_2b.o 

all: $(EXEC)

$(EXEC): $(OBJ)

	$(CC) -g -Wall -o ask1_2b ask1_2b.c -lpthread

run: $(EXEC) 
	./$(EXEC) $(ARG)

clean:
	rm -f $(OBJ) $(EXEC)