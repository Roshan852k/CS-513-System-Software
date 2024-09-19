/*  
============================================================================
Name : 1b.c
Author : Roshan Yadav
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
              b. ITIMER_VIRTUAL
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/time.h> 
#include<signal.h>

void timer_handler(int signum) {
    printf("Virtual Timer Expired\n");
    printf("Signal Received\n");
}

void main(){
    int timerStatus; 
    struct itimerval time;
    
    signal(SIGVTALRM, timer_handler);   // signum = 26
    
    time.it_interval.tv_sec = 10;
    time.it_interval.tv_usec = 0;
    time.it_value.tv_sec = 10;
    time.it_value.tv_usec = 0;
    
    setitimer(ITIMER_VIRTUAL, &time, NULL);
      
    while(1);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 1b.c -o 1b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./1b
Virtual Timer Expired
Signal Received
Virtual Timer Expired
Signal Received
Virtual Timer Expired
Signal Received
Virtual Timer Expired
Signal Received
Virtual Timer Expired
Signal Received
Virtual Timer Expired
Signal Received
^C


============================================================================
*/
