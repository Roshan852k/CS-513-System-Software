/*  
============================================================================
Name :10c.c
Author : Roshan Yadav
Description : Write a separate program using sigaction system call to catch the following signals.
              c. SIGFPE
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void floating_point_exception(int signum) {
    printf("Caught Signal - %d \n", signum);
    exit(0);
}

void main(){
    struct sigaction action;
    action.sa_handler = floating_point_exception;
    action.sa_flags = 0;
    
    int i = 10,j;
    sigaction(SIGFPE, &action, NULL); // signum = 8 
    j = i/0;
          
    return;
}

/*
===========================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 10c.c -o 10c
10c.c: In function ‘main’:
10c.c:27:10: warning: division by zero [-Wdiv-by-zero]
   27 |     j = i/0;
      |          ^
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./10c
Signal Catch
============================================================================
*/
