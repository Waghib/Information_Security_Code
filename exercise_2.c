#include "exercise_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_DATA_SIZE 256

void serve_welcome_response(int the_connection) {
    char buffer[32]; // buffer to hold the client's name
    memset(buffer, 0, 32); // Clear the buffer for receiving

    // Send the query to the client...
    write(the_connection, "Please enter your name:", 24);

    // Get the client's name...
    read(the_connection, buffer, MAX_DATA_SIZE);

    // // Option 1: Using printf
    // printf("Welcome message: %s\n", buffer);

    // // Option 2: Using write
    // const char *message = "Welcome to the server!\n";
    // write(STDOUT_FILENO, message, strlen(message));


    // Print the received message locally...
    printf("Message received: ");
    printf("%s", buffer);
    printf("\n");

    // Send the message back to the client to welcome them...
    write(the_connection, "Welcome ", 8); // Send 8 characters
    write(the_connection, buffer, strlen(buffer));
    return;
}

int server_loop(int port_number) {
    int sockfd, newsockfd;

    // Establish a socket for this server to listen on...
    sockfd = create_socket(port_number);

    for (;;) { // Loop forever
        // Accept a new connection - get a 'new socket fd' to handle it...
        newsockfd = accept_connection(sockfd);

        // Serve the client...
        serve_welcome_response(newsockfd);

        // We've now finished with this 'new socket file descriptor'
        close(newsockfd);
    }
}

int main(int argc, char *argv[]) {
    int port_number;

    if (argc < 2) {
        printf("ERROR: no port provided\n");
        exit(-1);
    } else {
        // Get the port number as provided on the command line...
        port_number = atoi(argv[1]);
        server_loop(port_number);
    }
}