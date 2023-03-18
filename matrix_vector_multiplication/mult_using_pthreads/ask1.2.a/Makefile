# Compiler
CC = gcc

# Executable
EXEC = ask1_2a

# Arguments
ARG = 6 3 3

# Object files
OBJ = ask1_2a.o 

all: $(EXEC)

$(EXEC): $(OBJ)

	$(CC) -g -Wall -o ask1_2a ask1_2a.c -lpthread

run: $(EXEC) 
	./$(EXEC) $(ARG)

clean:
	rm -f $(OBJ) $(EXEC)