/*  
============================================================================
Name : 15.c
Author : Roshan Yadav
Description : Write a simple program to send some data from parent to the child process.
Date: 12th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main(){
    int pipefd[2];                // pipefd[0] -> read, pipefd[1] -> write
    char buff[] = "Hello, Roshan"; 
    int pipe_status;           
    int readBytes, writeBytes; 
    
    pipe_status = pipe(pipefd); 
  
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
    } 
    else if (pid > 0) {
        close(pipefd[0]); // read end of parent will be close  
        writeBytes = write(pipefd[1], buff, sizeof(buff));
    } 
    else {
        close(pipefd[1]); // write end of parent will be close
        readBytes = read(pipefd[0], buff, sizeof(buff)); // 3 argumnet - writeBuffer??
        if (readBytes == -1)
            perror("Error while reading from pipe!");
        else
            printf("Data from pipe: %s\n", buff);
    }
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 15.c -o 15
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./15
Data from pipe: Hello, Roshan
============================================================================
*/
