/*  
============================================================================
Name :12.c
Author : Roshan Yadav
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 10th Sep, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void parent_process() {
    printf("Parent PID: %d\n", getpid());
    sleep(1);  
    printf("Parent is exiting...\n");
    exit(0); 
}

void child_process(pid_t parent_pid) {
    printf("Child PID: %d, Parent PID: %d\n", getpid(), parent_pid);
    
    sleep(2);
    
    printf("Child sending SIGKILL to Parent...\n");
    kill(parent_pid, SIGKILL);

    sleep(1);  
    printf("Child is now an orphan, Parent is gone.\n");
    printf("Parent PID: %d\n", getppid());

    exit(0);
}

void main(){
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid > 0) {
        parent_process();
    } else {
        child_process(getppid());
    }
          
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 12.c -o 12
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./12
Parent PID: 4736
Child PID: 4737, Parent PID: 4736
Parent is exiting...
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ Child sending SIGKILL to Parent...
Child is now an orphan, Parent is gone.
Parent PID: 1766
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-oroshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ps 1766
    PID TTY      STAT   TIME COMMAND
   1766 ?        Ss     0:00 /lib/systemd/systemd --user

============================================================================
*/
