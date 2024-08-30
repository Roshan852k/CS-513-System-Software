/* 
============================================================================
Name : 30.
Author : Roshan Yadav
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 30th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(){	
      if(!fork()){
            setsid();
            umask(0);
            while(1){
                sleep(4);
                printf("Child process pid:%d\n", getpid());
                printf("Daemon process is running\n");
            }
      }
      else{
	      exit(0);
      }
      return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 30.c -o 30
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./30
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ Child process pid:7268
Daemon process is running
^C
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ Child process pid:7268
Daemon process is running
Child process pid:7268
Daemon process is running
Child process pid:7268
Daemon process is running
Child process pid:7268
Daemon process is running
Child process pid:7268
Daemon process is running
Child process pid:7268
Daemon process is running
Child process pid:7268
Daemon process is running
Child process pid:7268
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~$ top -p 7268

top - 13:52:44 up  1:08,  2 users,  load average: 1.89, 1.75, 1.48
Tasks:   1 total,   0 running,   1 sleeping,   0 stopped,   0 zombie
%Cpu(s):  7.7 us,  0.6 sy,  0.0 ni, 91.7 id,  0.0 wa,  0.0 hi,  0.1 si,  0.0 st 
MiB Mem :   7670.3 total,   3116.5 free,   3086.6 used,   2498.8 buff/cache     
MiB Swap:   4096.0 total,   4096.0 free,      0.0 used.   4583.8 avail Mem
============================================================================
*/