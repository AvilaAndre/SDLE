CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
LINKER = lib/ -lzmq
BIN = bin/

	# gcc -Wall -I /usr/local/include server.c -L /usr/local/lib -lzmq -o output/server


# Targets
.PHONY: all
all: $(BIN)/client


$(BIN)/client: client.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

.PHONY: run_client1
run_client1: $(BIN)/client
	./$(BIN)/client 5555 5556

.PHONY: run_client2
run_client2: $(BIN)/client
	./$(BIN)/client 5556 5555

.PHONY: clean
clean:
	rm -f $(BIN)/client