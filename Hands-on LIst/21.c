/* Name - Roshan Yadav
   Roll No - MT2024169
   
   Problem - Write a program, call fork and print the parent and child process id.
*/

#include <stdio.h>
#include <unistd.h>  
#include <sys/types.h>  

int main() {
    pid_t p_pid, c_pid;

    p_pid = getpid();
    printf("Parent process ID: %d\n", p_pid);
    
    c_pid = fork();
    if(c_pid!=0)
      printf("Child process ID: %d\n", c_pid);

    return 0;
}


/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 21.c -o 21
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./21
Parent process ID: 6910
Child process ID: 6911
*/
