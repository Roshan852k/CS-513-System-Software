/*  
============================================================================
Name : 6.c
Author : Roshan Yadav
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 23th Aug, 2024.
============================================================================
*/

#include <unistd.h>
#include <stdio.h>  

void main()
{
    char *buffer[1];
    int CountSourcRead, CountDestinationWrite;
    while(1)
    {
        CountSourcRead = read(STDIN_FILENO, buffer, 1);
        CountDestinationWrite = write(STDOUT_FILENO, buffer, 1);

        if (CountSourcRead == -1 || CountDestinationWrite == -1)
        {
            printf("Error while reading or writing");
            break;
        }
    }
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 6.c -o 6
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./6
My name is Roshan Yadav
My name is Roshan Yadav
============================================================================
*/