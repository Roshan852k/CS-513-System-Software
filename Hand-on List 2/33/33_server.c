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
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<netinet/in.h>

void main(){
    
    struct sockaddr_in server, client;
    int sd, nsd;
    char buf[80];
    int port = 5050;
    
    sd = socket(AF_UNIX, SOCK_STREAM, 0); // IP protocol
    
    server.sin_family = AF_UNIX;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    bind(sd, (void*)&server, sizeof(server));
    listen(sd,5);
    
    int sz = sizeof(client);
    nsd = accept(sd, (void*)&client, &sz);
    read(nsd,buf,sizeof(buf));
    printf("Message from client: %s\n", buf);
    write(nsd,"Hello User\n", 13);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 33_server.c -o 33_server
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./33_server
Message from client: Hello User

============================================================================
*/
