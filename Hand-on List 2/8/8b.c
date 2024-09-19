/*  
============================================================================
Name : 8b.c
Author : Roshan Yadav
Description : Write a separate program using signal system call to catch the following signals.
              b. SIGINT
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void interrupt_handler(int signum) {
    printf("\nSignal Catch\n");
}

void main(){
    
    signal(SIGINT, interrupt_handler); // signum = 2
    
    while(1);
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 8b.c -o 8b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./8b
^C
Signal Catch

============================================================================
*/
