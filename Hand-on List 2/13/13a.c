/*  
============================================================================
Name : 13a.c
Author : Roshan Yadav
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). 
              Find out whether the first program is able to catch the signal or not.
Date: 10th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<signal.h>  
#include<unistd.h>

void customHandler()    // SIGDTOP Signal can;t catch
{
    printf("SIGSTOP signal received!\n");
    _exit(0);
}

void main(){

    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);

    signal(SIGSTOP, customHandler); 

    printf("Putting the process to sleep for 5s\n");
    sleep(5);
    
    printf("No stop signal received\n");

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 13a.c -o 13a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./13a
Process ID: 6355
Putting the process to sleep for 5s
No stop signal received
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./13a
Process ID: 6370
Putting the process to sleep for 5s

[4]+  Stopped                 ./13a
============================================================================
*/
