/*   
============================================================================
Name : 25.c
Author : Roshan Yadav
Description : Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).
Date: 28th Aug, 2024.
============================================================================
*/

#include<unistd.h>    
#include<sys/types.h> 
#include<sys/wait.h>  
#include<stdio.h>     

void main()
{
    pid_t child_a, child_b, child_c, terminatedChild;
    int waitStatus;

    if ((child_a = fork()) == 0)
    {
        printf("Child A created\n");
        printf("Settling child B down to sleep for 5 seconds\n");
        sleep(5);
        printf("Child A is now up\n");
        //_exit(0);
    }
    else
    {
        if ((child_b = fork()) == 0)
        {
            printf("Child B created\n");
            printf("Settling child B down to sleep for 10 seconds\n");
            sleep(10);
            printf("Child B is now up\n");
            _exit(0);
        }
        else
        {
            if ((child_c = fork()) == 0)
            {
                printf("Child C created\n");
                printf("Settling child B down to sleep for 15 seconds\n");
                sleep(15);
                printf("Child C is now up\n");
                _exit(0);
            }
            else
            {
                terminatedChild = waitpid(child_c, &waitStatus, 0);

                if (terminatedChild == child_c)
                {
                    if (waitStatus == 0)
                        printf("Child C has terminated with exit status = 0\n");
                    else
                        printf("Child has exited with exit status : %d\n", waitStatus);
                }
            }
        }
    }
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 25.c -o 25
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./25
Child A created
Settling child B down to sleep for 5 seconds
Child B created
Settling child B down to sleep for 10 seconds
Child C created
Settling child B down to sleep for 15 seconds
Child A is now up
Child B is now up
Child C is now up
Child C has terminated with exit status = 0
============================================================================
*/