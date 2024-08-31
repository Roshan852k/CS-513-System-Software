/*   
============================================================================
Name : 19.c
Author : Roshan Yadav
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 28th Aug, 2024.
============================================================================
*/

#include<stdio.h> 
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h> 
#include<sys/types.h>

static __inline__ unsigned long long rdtsc(void){
    unsigned int dst;
    __asm__ __volatile__("rdtsc" : "=A" (dst));
    return dst;
}

void main(){
    unsigned long long start, end;

    start = rdtsc();
    pid_t pid = getpid();
    end = rdtsc();
    
    printf("Process ID: %d\n", pid);
    printf("Time taken for getpid() system call: %llu\n", end - start);
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 19.c -o 19
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./19
Process ID: 4892
Time taken for getpid() system call: 12390
============================================================================
*/
