/*  
============================================================================
Name : 18.c
Author : Roshan Yadav
Description : Write a program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
Date: 13th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main(){
    int fd1[2], fd2[2];                // pipefd[0] -> read, pipefd[1] -> write
    int pipe_status_1, pipe_status_2;           
    
    pipe_status_1 = pipe(fd1); 
    pipe_status_2 = pipe(fd2); 
  
    int pid = fork();
    if (pid==0) {
        dup2(fd1[1], 1); // write end of pipe1 open
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        execlp("ls", "ls", "-Rl",NULL);
    }
    else {
        int pid = fork();
        if (pid==0) {
            dup2(fd1[0], 0); // read end of pipe1 open
            dup2(fd2[1], 1); // write end of pipe2 open
            close(fd1[1]);
            close(fd2[0]);
            execlp("grep", "grep", "^d",NULL);
            }
        else {
            dup2(fd2[0], 0); // read end of pipe2 open
            close(fd2[1]);
            close(fd1[0]);
            close(fd1[1]);
            execlp("wc", "wc",NULL);
        }
    } 
    return;
}
/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 18.c -o 18
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ls -l | grep ^d
drwxrwxr-x 2 roshan roshan  4096 Sep 20 12:39 MY
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./18
      1       9      49
============================================================================
*/
