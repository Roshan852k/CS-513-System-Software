/*  
============================================================================
Name : 5.c
Author : Roshan Yadav
Description : 5. Write a program to print the system limitation of
              a. maximum length of the arguments to the exec family of functions.
              b. maximum number of simultaneous process per user id.
              c. number of clock ticks (jiffy) per second.
              d. maximum number of open files
              e. size of a page
              f. total number of pages in the physical memory
              g. number of currently available pages in the physical memory.
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main(){

    // a. Maximum length of the arguments to the exec family of functions
    long max_arg_length = sysconf(_SC_ARG_MAX);
    printf("Maximum length of arguments to exec: %ld bytes\n", max_arg_length);
    
    // b. maximum number of simultaneous process per user id.
    long proc_limit = sysconf(_SC_ARG_MAX);
    printf("Maximum number of simultaneous processes per user id: %lu\n", proc_limit);

    // c. Number of clock ticks (jiffy) per second
    long clock_ticks = sysconf(_SC_CLK_TCK);
    printf("Number of clock ticks (jiffy) per second: %ld\n", clock_ticks);

    // d. Maximum number of open files
    long open_files_limit = sysconf(_SC_ARG_MAX);
    printf("Maximum number of open files: %lu\n", open_files_limit);

    // e. Size of a page
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Size of a page: %ld bytes\n", page_size);

    // f. Total number of pages in physical memory
    long total_pages = sysconf(_SC_PHYS_PAGES);
    printf("Total number of pages in physical memory: %ld\n", total_pages);
    
    // g. Number of currently available pages in the physical memory.
    long available_pages = sysconf(_SC_ARG_MAX);
    printf("Number of currently available pages in physical memory: %ld\n", available_pages);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 5.c -o 5
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./5
Maximum length of arguments to exec: 2097152 bytes
Maximum number of simultaneous processes per user id: 2097152
Number of clock ticks (jiffy) per second: 100
Maximum number of open files: 2097152
Size of a page: 4096 bytes
Total number of pages in physical memory: 1963600
Number of currently available pages in physical memory: 2097152
============================================================================
*/
