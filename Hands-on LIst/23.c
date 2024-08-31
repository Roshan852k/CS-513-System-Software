/*  
============================================================================
Name : 23.c
Author : Roshan Yadav
Description : Write a program to create a Zombie state of the running program.
Date: 28th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main() {
    if(!fork()){
        printf("Child pid: %d\n", getpid());
    }
    else{
        getchar();
    }   
    return ;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 23.c -o 23
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./23
Child pid: 4127

============================================================================
*/


