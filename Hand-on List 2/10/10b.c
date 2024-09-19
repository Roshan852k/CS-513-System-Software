/*  
============================================================================
Name :10.c
Author : Roshan Yadav
Description : Write a separate program using sigaction system call to catch the following signals.
              b. SIGINT
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void interrupt_handler(int signum) {
    printf("\nSignal Catch\n");
    exit(1);
}

void main(){
    struct sigaction action;
    action.sa_handler = interrupt_handler;
    action.sa_flags = 0;
    
    sigaction(SIGINT, &action, NULL); // signum = 2
    while(1);
          
    return;
}

/*
===========================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 10b.c -o 10b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./10b
^C
Signal Catch
============================================================================
*/
