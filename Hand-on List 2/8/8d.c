/*  
============================================================================
Name : 8d.c
Author : Roshan Yadav
Description : Write a separate program using signal system call to catch the following signals.
              d. SIGALRM (use alarm system call)
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
#include<signal.h>

void timer_handler(int signum) {
    printf("Signal Catch\n");
}

void main(){
    struct itimerval time;
    
    signal(SIGALRM, timer_handler); // signum = 14
    
    alarm(1);
    
    while(1);
    
    return;
}

/*
============================================================================
rroshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 8d.c -o 8d
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./8d
Signal Catch
^C
============================================================================
*/
