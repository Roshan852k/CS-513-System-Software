/*  
============================================================================
Name : 13a.c
Author : Roshan Yadav
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). 
              Find out whether the first program is able to catch the signal or not.
Date: 10th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>  
#include<unistd.h>
#include <stdlib.h>

void main(int argc, char *argv[]){

    pid_t pid;
    pid = atoi(argv[1]);

    int killStatus = kill(pid, SIGSTOP);
    printf("Successfully sent SIGSTOP signal to process (%d)\n", pid);

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 13b.c -o 13b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./13b 6370
Successfully sent SIGSTOP signal to process (6370)
============================================================================
*/
