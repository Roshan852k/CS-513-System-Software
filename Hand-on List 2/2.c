/*  
============================================================================
Name : 2.c
Author : Roshan Yadav
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/resource.h>
#include<limits.h> 

void print(const char *name, rlim_t  cur, rlim_t max, const char *unit) {
    printf("%s: SoftLimit = %lu, Hardimit = %lu %s\n", name, (unsigned long)cur, (unsigned long)max, unit);
    printf("---------------------------------------------------------------------------------------\n");
}

void main(){
    struct rlimit resourceLimits; 
    
    // RLIMIT_CORE -> Max size of a core file
    int limit = getrlimit(RLIMIT_CORE, &resourceLimits);
    print("Max size of a core file",resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");
    
    // RLIMIT_AS -> This  is  the maximum size of the process's virtual memory (address space).
    limit = getrlimit(RLIMIT_AS, &resourceLimits);
    print("Max size of process's virtual memory", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");
    
    // RLIMIT_CPU -> Amount of CPU time that the process can consume
    limit = getrlimit(RLIMIT_CPU, &resourceLimits);
    print("Max CPU time that the process can consume", resourceLimits.rlim_cur, resourceLimits.rlim_max, "seconds");

    // RLIMIT_DATA -> Maximum size of the process's data segment
    limit = getrlimit(RLIMIT_DATA, &resourceLimits);
    print("Max size of process's data segement", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_FSIZE -> Maximum size of files that  the  process  may  create
    limit = getrlimit(RLIMIT_FSIZE, &resourceLimits);
    print("Max size of files that  the  process  may  create", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_LOCKS -> Maximum number of locks that a process may establish
    limit = getrlimit(RLIMIT_LOCKS, &resourceLimits);
    print("Max number of locks that a process may establish", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_MEMLOCK -> Maximum number of bytes of memory that may be locked into RAM
    limit = getrlimit(RLIMIT_MEMLOCK, &resourceLimits);
    print("Max number of bytes of memory that may be locked into RAM", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_MSGQUEUE -> Maximum number of bytes that can be allocated for POSIX message queues
    limit = getrlimit(RLIMIT_MSGQUEUE, &resourceLimits);
    print("Max number of bytes of that can be allocated for POSIX message queues", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_NICE -> Ceiling of the process's nice value
    limit = getrlimit(RLIMIT_NICE, &resourceLimits);
    print("Ceiling of the process's nice value", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_NOFILE -> specifies a value one greater than the maximum file descriptor number that can be opened by this process
    limit = getrlimit(RLIMIT_NOFILE, &resourceLimits);
    print("Max file descriptor", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_NPROC -> Limit on the number of threads
    limit = getrlimit(RLIMIT_NPROC, &resourceLimits);
    print("Limit on the number of threads", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_RSS -> Limit on the number of virtual pages resident in the RAM
    limit = getrlimit(RLIMIT_RSS, &resourceLimits);
    print("Limit on the  number of virtual pages resident in the RAM", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_RTPRIO -> a ceiling on the real-time priority
    limit = getrlimit(RLIMIT_RTPRIO, &resourceLimits);
    print("Ceiling on the real-time priority", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_RTTIME -> Amount of CPU time that a  process scheduled  under a real-time scheduling policy may consume without making a blocking system call.
    limit = getrlimit(RLIMIT_RTTIME, &resourceLimits);
    print("Amount of CPU time that a  process scheduled  under a real-time scheduling policy", resourceLimits.rlim_cur, resourceLimits.rlim_max, "ms");
    
    // RLIMIT_SIGPENDING ->The number of signals that may be queued
    limit = getrlimit(RLIMIT_SIGPENDING, &resourceLimits);
    print("The number of signals that may be queued", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_STACK -> Maximum  size of the process stack
    limit = getrlimit(RLIMIT_STACK, &resourceLimits);
    print("Maximum  size of the process stack", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 2.c -o 2
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./2
Max size of a core file: SoftLimit = 0, Hardimit = 18446744073709551615 bytes
---------------------------------------------------------------------------------------
Max size of process's virtual memory: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 bytes
---------------------------------------------------------------------------------------
Max CPU time that the process can consume: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 seconds
---------------------------------------------------------------------------------------
Max size of process's data segement: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 bytes
---------------------------------------------------------------------------------------
Max size of files that  the  process  may  create: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 bytes
---------------------------------------------------------------------------------------
Max number of locks that a process may establish: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 
---------------------------------------------------------------------------------------
Max number of bytes of memory that may be locked into RAM: SoftLimit = 1005363200, Hardimit = 1005363200 bytes
---------------------------------------------------------------------------------------
Max number of bytes of that can be allocated for POSIX message queues: SoftLimit = 819200, Hardimit = 819200 bytes
---------------------------------------------------------------------------------------
Ceiling of the process's nice value: SoftLimit = 0, Hardimit = 0 
---------------------------------------------------------------------------------------
Max file descriptor: SoftLimit = 1024, Hardimit = 1048576 bytes
---------------------------------------------------------------------------------------
Limit on the number of threads: SoftLimit = 30388, Hardimit = 30388 
---------------------------------------------------------------------------------------
Limit on the  number of virtual pages resident in the RAM: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 bytes
---------------------------------------------------------------------------------------
Ceiling on the real-time priority: SoftLimit = 0, Hardimit = 0 
---------------------------------------------------------------------------------------
Amount of CPU time that a  process scheduled  under a real-time scheduling policy: SoftLimit = 18446744073709551615, Hardimit = 18446744073709551615 ms
---------------------------------------------------------------------------------------
The number of signals that may be queued: SoftLimit = 30388, Hardimit = 30388 
---------------------------------------------------------------------------------------
Maximum  size of the process stack: SoftLimit = 8388608, Hardimit = 18446744073709551615 bytes
---------------------------------------------------------------------------------------
============================================================================
*/
