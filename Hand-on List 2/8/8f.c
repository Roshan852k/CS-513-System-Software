/*  
============================================================================
Name : 8f.c
Author : Roshan Yadav
Description : Write a separate program using signal system call to catch the following signals.
              f. SIGVTALRM (use setitimer system call)
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/time.h>
#include<signal.h>

void timer_handler(int signum) {
    printf("Signal Catch\n");
}

void main(){
    struct itimerval time;
    
    signal(SIGVTALRM, timer_handler);  // signum = 26
    
    time.it_value.tv_sec = 1;
    time.it_value.tv_usec = 0;
    
    setitimer(ITIMER_VIRTUAL, &time, NULL);
      
    while(1);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 8f.c -o 8f
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./8f
Signal Catch
^C
============================================================================
*/
