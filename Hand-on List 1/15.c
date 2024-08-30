/*   
============================================================================
Name : 15.c
Author : Roshan Yadav
Description : Write a program to display the environmental variable of the user (use environ).
Date: 25th Aug, 2024.
============================================================================
*/

#include<stdio.h>
extern char **environ;

int isUser(char *var)
{
    return var[0] == 'U' && var[1] == 'S' && var[4] == '=';
}

void main()
{
    int iter = -1;
    while (environ[++iter] != NULL){
        if (isUser(environ[iter])){
            printf("%s\n", environ[iter]);
        }
    }
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 15.c -o 15
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./15
USER=roshan
============================================================================
*/


