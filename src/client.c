// Client side C program
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
# include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <string.h>
#define PORT 9092
int createSocket(int domain, int type, int protocol)
{
    int sockfd = socket(domain, type, protocol);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return -1;
    }
    printf("Socket created successfully!\n");
    return sockfd;
}

void connetSocket(int sockfd, const char* server_ip, unsigned short port) {
    int opt = 1; // This is the variable to reuse address and port

    // Set socket options to reuse address and port
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // Clear structure
    server_addr.sin_family = PF_INET;            // IPv4
    server_addr.sin_port = htons(port);          // Set port

    if (inet_pton(PF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", server_ip, port);
}


int main(int argc, char const* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* server_ip = argv[1];
    unsigned short port = (unsigned short)atoi(argv[2]);

    int sockfd = createSocket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    connetSocket(sockfd, server_ip, port);
    close(sockfd);

    return 0;
}
