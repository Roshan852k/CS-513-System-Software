/*  
============================================================================
Name : 8d.c
Author : Roshan Yadav
Description : Write a separate program using signal system call to catch the following signals.
              a. SIGSEGV
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void error_handler(int signum) {
    printf("Signal Catch\n");
    exit(1);
}

void main(){
    
    signal(SIGSEGV, error_handler); // signum = 11
    
    int *ptr = NULL; 
    *ptr = 42; //
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 8a.c -o 8a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./8a
Signal Catch
============================================================================
*/
