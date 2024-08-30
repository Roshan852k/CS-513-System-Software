/* 
      Name - Roshan Yadav
      Roll No - MT2024169
      Problem - Write a program to execute ls -Rl by the following system calls
                d. execv
*/

#include<stdio.h>
#include<unistd.h>

void main(){
      char* arg[] ={"/bin/ls", "-Rl","./my-repo",NULL};
      execv(arg[0], arg);
      return;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 27d.c -o 27d
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./27d
./my-repo:
total 152
-rw-r--r-- 1 roshan roshan    790 Aug 27 18:20 1a.c
-rw-rw-rw- 1 roshan roshan    768 Aug 27 18:32 1b.c
-rw-rw-r-- 1 roshan roshan   1291 Aug 27 18:35 1c.c
-rw-rw-r-- 1 roshan roshan   2265 Aug 25 01:03 2.c
-rw-rw-r-- 1 roshan roshan    823 Aug 27 18:47 3.c
-rw-rw-r-- 1 roshan roshan    900 Aug 27 18:49 4.c
-rw-rw-r-- 1 roshan roshan 108549 Aug 27 19:10 5.c
-rw-rw-r-- 1 roshan roshan    825 Aug 25 00:22 6.c
-rw-rw-r-- 1 roshan roshan   1296 Aug 27 19:12 7.c
-rw-rw-r-- 1 roshan roshan   1038 Aug 27 19:14 8.c
-rw-rw-r-- 1 roshan roshan   1689 Aug 25 00:58 9.c
-rw-rw-r-- 1 roshan roshan     35 Aug 21 19:43 README.md
*/


