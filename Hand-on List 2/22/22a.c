/*  
============================================================================
Name : 22a.c
Author : Roshan Yadav
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 10th Sep, 2024.
==========================================================================
*/

#include<stdio.h> 
#include<fcntl.h>
#include<unistd.h> 
#include<sys/time.h>  
#include<sys/types.h> 

void main()
{
    char buffer[100]; 
    fd_set readFDSet;
    struct timeval time;
    
    int file_desc  = open("fifo", O_RDONLY);
 
    FD_ZERO(&readFDSet);
    FD_SET(file_desc, &readFDSet);

    time.tv_sec = 10;
    time.tv_usec = 0;

    int returnVal = select(file_desc+ 1, &readFDSet, NULL, NULL, &time);

    if (returnVal == -1){
        printf("ERROR");
    }
    else if (returnVal){
        printf("The data is now available\n");
    }
    else{
        printf("No data was given for 10 seconds\n");
        _exit(0);
    }
    
    read(file_desc, buffer, 100);
    printf("The text from the FIFO : %s\n", buffer);

    close(file_desc); 
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 22a.c -o 22a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./22a
The data is now available
The text from the FIFO : Roshan
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./22a
No data was given for 10 seconds
============================================================================
*/
