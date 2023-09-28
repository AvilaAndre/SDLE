CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
LINKER = lib/ -lzmq
BIN = bin/

	# gcc -Wall -I /usr/local/include server.c -L /usr/local/lib -lzmq -o output/server


# Targets
.PHONY: all
all: $(BIN)/worker $(BIN)/client $(BIN)/broker

$(BIN)/worker: worker.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

$(BIN)/client: client.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

$(BIN)/broker: broker.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

.PHONY: run_worker
run_worker: $(BIN)/worker
	./$(BIN)/worker

.PHONY: run_client
run_client: $(BIN)/client
	./$(BIN)/client $(ARGS)

.PHONY: run_broker
run_broker: $(BIN)/broker
	./$(BIN)/broker $(ARGS)


.PHONY: clean
clean:
	rm -f $(BIN)/worker
	rm -f $(BIN)/client
	rm -f $(BIN)/broker