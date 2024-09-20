/*  
============================================================================
Name : 17b.c
Author : Roshan Yadav
Description : Write a program to execute ls -l | wc.
              b. use dup2
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
        close(pipefd[0]);   // read end of child will be close  
        dup2(pipefd[1],1); 
        execlp("ls","ls","-l",NULL);  // name of file, name of programe(arg1), additional format(arg2), NULL(argumnet end)
    } 
    else {
        close(pipefd[1]); // write end of parent will be close
        dup2(pipefd[0],0); 
        execlp("wc","wc", NULL);
    }
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 17b.c -o 17b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./17b
     85     758    4277
============================================================================
*/
