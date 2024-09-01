# Variables
CC = gcc
CFLAGS = -Wall
CLIENT_TARGET = client

# source files
CLIENT_SRC = src/client.c

# Compile both by default
all: $(CLIENT_TARGET)

# Rule to compile the client
$(CLIENT_TARGET): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_TARGET) $(CLIENT_SRC)

# Run the client
run_client: $(CLIENT_TARGET)
	./$(CLIENT_TARGET)

# Clean
clean:
	rm -f $(CLIENT_TARGET)
