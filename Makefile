# Variables
CC = gcc
CFLAGS = -Wall
CLIENT_TARGET = client

# Source files
CLIENT_SRC = src/client.c

# Compile both by default
all: $(CLIENT_TARGET)

# Rule to compile the client
$(CLIENT_TARGET): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_TARGET) $(CLIENT_SRC)

# Run the client with parameters
run_client: $(CLIENT_TARGET)
	@echo "Running client with IP and port as parameters."
	./$(CLIENT_TARGET) $(IP) $(PORT)

# Clean
clean:
	rm -f $(CLIENT_TARGET)
