/*  
    Name - Roshan Yadav
    Roll No - MT2024169  
    Problem - Write a program, call fork and print the parent and child process id.
*/

#include<stdio.h>
#include<unistd.h>  
#include<sys/types.h>  

void main(){
    pid_t p_pid, c_pid;

    p_pid = getpid();
    printf("Parent process ID: %d\n", p_pid);
    
    c_pid = fork();
    if(c_pid!=0){
        printf("Child process ID: %d\n", c_pid);
    }
    return;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 20.c -o 20
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./20
Current priority of process wih pid 5239: 0
New priority of process wih pid 5239: 10
*/
