CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
LINKER = lib/ -lzmq
BIN = bin/

	# gcc -Wall -I /usr/local/include server.c -L /usr/local/lib -lzmq -o output/server


# Targets
.PHONY: all
all: $(BIN)/publisher $(BIN)/subscriber $(BIN)/proxy

$(BIN)/publisher: publisher.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

$(BIN)/subscriber: subscriber.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

$(BIN)/proxy: proxy.c
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE) -L $(LINKER)

.PHONY: run_publisher
run_publisher: $(BIN)/publisher
	./$(BIN)/publisher

.PHONY: run_subscriber
run_subscriber: $(BIN)/subscriber
	./$(BIN)/subscriber $(ARGS)

.PHONY: run_proxy
run_proxy: $(BIN)/proxy
	./$(BIN)/proxy $(ARGS)


.PHONY: clean
clean:
	rm -f $(BIN)/publisher
	rm -f $(BIN)/subscriber
	rm -f $(BIN)/proxy