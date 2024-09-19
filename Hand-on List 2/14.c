/*  
============================================================================
Name : 14.c
Author : Roshan Yadav
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 10th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h> 

void main(){

    int pipefd[2];                // pipefd[0] -> read, pipefd[1] -> write
    char buff[] = "Hello, Roshan"; 
    int pipe_status;           
    int readBytes, writeBytes; 
    
    pipe_status = pipe(pipefd); 

    printf("Writing to the pipe!\n");
    writeBytes = write(pipefd[1], buff, sizeof(buff));
    
    if (writeBytes == -1)
        perror("Error while writing to pipe!");
    else
    {
        printf("Now reading from the pipe!\n");
        readBytes = read(pipefd[0], buff, sizeof(buff));
        if (readBytes == -1)
            perror("Error while reading from pipe!");
        else
            printf("Data from pipe: %s\n", buff);
    }
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 14.c -o 14
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./14
Writing to the pipe!
Now reading from the pipe!
Data from pipe: Hello, Roshan
============================================================================
*/
