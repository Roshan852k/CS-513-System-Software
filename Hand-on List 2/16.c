/*  
============================================================================
Name : 16.c
Author : Roshan Yadav
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date: 12th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main(){
    int pipe1fd[2], pipe2fd[2];                // pipefd[0] -> read, pipefd[1] -> write
    char buff1[] = "Hello, Child";             // message from parent    
    char buff2[] = "Hello, Parent";            // message from child   
    int pipe_status_1, pipe_status_2;           
    int readBytes, writeBytes; 
    
    pipe_status_1 = pipe(pipe1fd); 
    pipe_status_2 = pipe(pipe2fd); 
  
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
    } 
    else if (pid > 0) {                                             //  Parent use read end of pipe1 & write end of pipe2 
        close(pipe1fd[1]); // write end of parent will be close
        close(pipe2fd[0]); // read end of parent will be close 
        readBytes = read(pipe1fd[0], buff2, sizeof(buff2)); 
        printf("Data from Child: %s\n", buff2);
        writeBytes = write(pipe2fd[1], buff1, sizeof(buff1));
    } 
    else {
        close(pipe1fd[0]); // read end of parent will be close  
        close(pipe2fd[1]); // write end of parent will be close  
        writeBytes = write(pipe1fd[1], buff2, sizeof(buff2));
        readBytes = read(pipe2fd[0], buff1, sizeof(buff1)); 
        printf("Data from Parent: %s\n", buff1);
    }
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 16.c -o 16
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./16
Data from Child: Hello, Parent
Data from Parent: Hello, Child
============================================================================
*/
