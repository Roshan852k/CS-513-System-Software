/*  
============================================================================
Name : 33.c
Author : Roshan Yadav
Description : Write a program to communicate between two machines using socket.
Date: 19th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

void main(){
    
    struct sockaddr_in server;
    int sd;
    char buf[80];
    int port = 5050;
    
    sd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    server.sin_family = AF_UNIX;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    connect(sd, (void*)&server, sizeof(server));
    write(sd,"Hello server\n",14);
    read(sd,buf,sizeof(buf));
    printf("Message from server: %s\n" , buf);
     
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 33_client.c -o 33_client
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./33_client
Message from server: Hello Client

============================================================================
*/
