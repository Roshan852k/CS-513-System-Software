/*  
============================================================================
Name :11.c
Author : Roshan Yadav
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
Date: 10th Sep, 2024.
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
    action.sa_handler = SIG_IGN;
    action.sa_flags = 0;
    
    printf("....Ignore Ctrl+C request");
    
    sigaction(SIGINT, &action, NULL); // signum = 2
    
    action.sa_handler = interrupt_handler;
    action.sa_flags = 0;
    
    // reset SIGINT signal
    sigaction(SIGINT, &action, NULL); // signum = 2
    
    while(1);
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 11.c -o 11
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./11
^C....Ignore Ctrl+C request
Signal Catch
============================================================================
*/
