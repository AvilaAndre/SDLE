CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
LINKER = lib/ -lzmq
BIN = bin/

	# gcc -Wall -I /usr/local/include server.c -L /usr/local/lib -lzmq -o output/server


# Targets
.PHONY: all
all: $(BIN)/server $(BIN)/client

$(BIN)/server: server.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

$(BIN)/client: client.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

.PHONY: run_server
run_server: $(BIN)/server
	./$(BIN)/server

.PHONY: run_client
run_client: $(BIN)/client
	./$(BIN)/client $(ARGS)

.PHONY: clean
clean:
	rm -f $(BIN)/server
	rm -f $(BIN)/client