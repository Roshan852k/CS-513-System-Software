/*  
============================================================================
Name : 23.c
Author : Roshan Yadav
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: 18th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h> 
#include<fcntl.h>


void main(){
    char *fifoName = "mkfifo";
    int fifoStatus = mkfifo(fifoName, S_IRWXU);
    
    long open_files_limit = sysconf(_SC_ARG_MAX);
    printf("Maximum number of open files: %lu\n", open_files_limit);
    
    long pipe_size = pathconf(fifoName, _PC_PIPE_BUF);
    printf("Size of pipe (circular buffer): %ld bytes\n", pipe_size);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 23.c -o 23
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./23
Maximum number of open files: 2097152
Size of pipe (circular buffer): 4096 bytes
============================================================================
*/
