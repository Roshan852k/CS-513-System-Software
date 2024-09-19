/*  
============================================================================
Name : 8c.c
Author : Roshan Yadav
Description : Write a separate program using signal system call to catch the following signals.
              c. SIGFPE
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void floating_point_exception(int signum) {
    printf("Signal Catch\n");
    exit(0);
}

void main(){
    int i = 10,j;
    signal(SIGFPE, floating_point_exception); // signum = 8
    
    j = i/0;
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 8c.c -o 8c
8c.c: In function ‘main’:
8c.c:24:10: warning: division by zero [-Wdiv-by-zero]
   24 |     j = i/0;
      |          ^
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./8c
Signal Catch
============================================================================
*/
