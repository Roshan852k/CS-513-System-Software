/*  
============================================================================
Name : 3.c
Author : Roshan Yadav
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/resource.h>

void main(){
    struct rlimit resourceLimits; 

    // RLIMIT_CORE -> Max size of a core file
    int limit = getrlimit(RLIMIT_CORE, &resourceLimits);

    printf("Before setting soft and hard limit\n");
    printf("Max size of a core file : SoftLimit = %lu, Hardimit = %lu %s\n", (unsigned long)resourceLimits.rlim_cur, (unsigned long)resourceLimits.rlim_max, "bytes");
    
    resourceLimits.rlim_cur = 0;
    resourceLimits.rlim_max = 100*1024; // 100KB
    printf("After setting soft and hard limit\n");
    printf("Max size of a core file : SoftLimit = %lu, Hardimit = %lu %s\n", (unsigned long)resourceLimits.rlim_cur, (unsigned long)resourceLimits.rlim_max, "bytes");
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 3.c -o 3
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./3
Before setting soft and hard limit
Max size of a core file: SoftLimit = 0, Hardimit = 18446744073709551615 bytes
After setting soft and hard limit
Max size of a core file: SoftLimit = 0, Hardimit = 102400 bytes
============================================================================
*/
