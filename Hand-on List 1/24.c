/* 
============================================================================
Name : 24.c
Author : Roshan Yadav
Description :  Write a program to create an orphan process.
Date: 28th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main() {
    if(!fork()){
        printf("Child pid before orphan: %d\n", getpid());
        printf("Child process going for 3 sec sleep\n");
        sleep(3);
        printf("Child pid after orphan:: %d\n", getpid());
    }
    else{
        printf("Parent pid: %d\n", getpid());
        printf("Parent process going for 1 sec sleep\n");
        sleep(1);
        printf("Parent exit\n");
    }   
    return ;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 24.c -o 24
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./24
Parent pid: 5281
Parent process going for 1 sec sleep
Child pid before orphan: 5282
Child process going for 3 sec sleep
Parent exit
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ Child pid after orphan:: 5282
^C
============================================================================
*/
