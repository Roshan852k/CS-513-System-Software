/*  
============================================================================
Name :9.c
Author : Roshan Yadav
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
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
    
    signal(SIGINT, SIG_IGN);
    printf("....Ignore Ctrl+C request");
    
    // reset SIGINT signal
    signal(SIGINT, interrupt_handler); // signum = 2
    
    while(1);
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 9.c -o 9
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./9
^C....Ignore Ctrl+C request
Signal Catch
============================================================================
*/
