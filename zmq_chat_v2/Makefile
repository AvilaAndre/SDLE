CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
LINKER = lib/ -lzmq
BIN = bin/

	# gcc -Wall -I /usr/local/include server.c -L /usr/local/lib -lzmq -o output/server


# Targets
.PHONY: all
all: $(BIN)/client $(BIN)/proxy

$(BIN)/client: client.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

$(BIN)/proxy: proxy.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

.PHONY: run_client
run_client: $(BIN)/client
	./$(BIN)/client $(ID)

.PHONY: run_proxy
run_proxy: $(BIN)/proxy
	./$(BIN)/proxy


.PHONY: clean
clean:
	rm -f $(BIN)/client
	rm -f $(BIN)/proxy