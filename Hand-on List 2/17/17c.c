/*  
============================================================================
Name : 17c.c
Author : Roshan Yadav
Description : Write a program to execute ls -l | wc.
              c. use fcntl
Date: 13th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h> 

void main(){
    int pipefd[2];                // pipefd[0] -> read, pipefd[1] -> write
    int pipe_status;           
    
    pipe_status = pipe(pipefd); 
  
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
    } 
    else if (pid == 0) {
        close(STDOUT_FILENO); 
        fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO);
        close(pipefd[0]);
        execlp("ls","ls","-l",NULL);  // name of file, name of programe(arg1), additional format(arg2), NULL(argumnet end)
    } 
    else {
        close(STDIN_FILENO);
        fcntl(pipefd[0], F_DUPFD, STDIN_FILENO);
        close(pipefd[1]);
        execlp("wc","wc", NULL);
    }
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 17c.c -o 17c
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./17c
     85     758    4277
============================================================================
*/
