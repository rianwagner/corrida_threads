EXEC = corrida_threads
CC = gcc
CFLAGS = -Wall -Wextra -pthread -g
SRC = corrida_threads.c
all: $(EXEC)
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)

rebuild: clean all run
