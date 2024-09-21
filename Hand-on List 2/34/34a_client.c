/*  
============================================================================
Name : 34_client.c
Author : Roshan Yadav
Description : Write a program to create a concurrent server.
              a. use fork
Date: 20th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int PORT = 8080;    

    // Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type messages to send:\n");

    while (1) {
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);

        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // Send message to the server
        write(sock, buffer, strlen(buffer));

        // Read response from the server
        int bytes_read = read(sock, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the received data
            printf("Server replied: %s", buffer);
        }
    }

    close(sock);
    printf("Disconnected from server.\n");
    return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 34a_client.c -o 34a_client

Client 1 - 
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./34a_client
Connected to server. Type messages to send:
> Hello Server
Server replied: Hello Server
>


Client 2 - 
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./34a_client
Connected to server. Type messages to send:
> Hello Server , My name is roshan
Server replied: Hello Server , My name is roshan
> 


============================================================================
*/
