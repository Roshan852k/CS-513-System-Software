/*  
============================================================================
Name : 17a.c
Author : Roshan Yadav
Description : Write a program to execute ls -l | wc.
              a. use dup
Date: 13th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

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
        dup(pipefd[1]);
        close(pipefd[0]);
        execlp("ls","ls","-l",NULL); 
    } 
    else {      
        close(STDIN_FILENO);
        dup(pipefd[0]);
        close(pipefd[1]);
        execlp("wc","wc", NULL);// name of file, name of programe(arg1), additional format(arg2), NULL(argumnet end)
    }
    wait(NULL);
          
    return ;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc -o 17a 17a.c
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./17a
     92     821    4633
============================================================================
*/
