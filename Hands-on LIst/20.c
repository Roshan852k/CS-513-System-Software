/*    
============================================================================
Name : 20.c
Author : Roshan Yadav
Description : Find out the priority of your running program. Modify the priority with nice command.
Date: 28th Aug, 2024.
============================================================================
*/

#include<stdio.h> 
#include<fcntl.h>
#include<sys/resource.h>
#include<unistd.h>

void main(){
    pid_t pid = getpid();
    int prior;
    
    prior = getpriority(PRIO_PROCESS, pid);
    printf("Current priority of process wih pid %d: %d\n", pid,prior);
    
    prior = nice(10);
    printf("New priority of process wih pid %d: %d\n", pid, prior);
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 20.c -o 20
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./20
Current priority of process wih pid 5239: 0
New priority of process wih pid 5239: 10
============================================================================
*/
