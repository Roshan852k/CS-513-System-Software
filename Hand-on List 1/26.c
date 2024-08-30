/*  
============================================================================
Name : 26.c
Author : Roshan Yadav
Description : Write a program to execute an executable program.
              a. use some executable program
              b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 30th Aug, 2024.
============================================================================
*/

#include<unistd.h>

void main()
{
    char *executable_prog = "./14";
    char *arg = "14.c";
    execl(executable_prog, executable_prog, arg, NULL);
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 26.c -o 26
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./26 hello.txt
Regular File
============================================================================
*/
