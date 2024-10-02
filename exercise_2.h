// Exercise 2: Stack Overflow and Direct Code Execution
// Header File
#include <stdio.h>    // for printf()
#include <unistd.h>   // for read() and write()
#include <stdlib.h>   // for exit()
#include <string.h>   // for memset() and strlen()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Function Prototypes
struct sockaddr_in cli_addr;
unsigned int clilen = sizeof(cli_addr);


// Function to display error message
void error(char *msg) {
    perror(msg);
    exit(1);
}

// Function to create a socket
int create_socket(int portno) {
    int sockfd;
    struct sockaddr_in serv_addr;
    int b; // result of bind()

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Initialize socket structure
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bind the host address
    b = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (b < 0)
        error("ERROR on binding");

    // Start listening for the clients    
    listen(sockfd, 5);
    return sockfd;
}

// Function to accept a connection
int accept_connection(int sockfd) {
    return accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
}