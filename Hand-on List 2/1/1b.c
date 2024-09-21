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
#include<stdlib.h>

void timer_handler(int signum) {
    printf("Virtual Timer Expired\n");
    printf("Signal Received\n");
    exit(1);
}

void main(int argc, char *argv[]){
    int timerStatus; 
    struct itimerval time;
    
    signal(SIGVTALRM, timer_handler);   // signum = 26
    
    
    if (argv[1][0] == '1')
    {
        time.it_interval.tv_sec = 0;
        time.it_interval.tv_usec = 0;
        time.it_value.tv_sec = 10;
        time.it_value.tv_usec = 0;
    }
    else if (argv[1][0] == '2')
    {
        time.it_interval.tv_sec = 0;
        time.it_interval.tv_usec = 0;
        time.it_value.tv_sec = 0;
        time.it_value.tv_usec = 10000;
    }
    
    setitimer(ITIMER_VIRTUAL, &time, NULL);
      
    while(1);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 1b.c -o 1b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./1b 1
Virtual Timer Expired
Signal Received
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./1b 2
Virtual Timer Expired
Signal Received
============================================================================
*/
