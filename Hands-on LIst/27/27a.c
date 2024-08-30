/*  
    Name - Roshan Yadav
    Roll No - MT2024169  
    Problem - Write a program to execute ls -Rl by the following system calls
              a. execl
*/

#include<stdio.h>
#include<unistd.h>

void main(){
    execl("/bin/ls", "ls", "-l", NULL);
    return;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 27a.c -o 27a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./27a
total 288
-rw-rw-r-- 1 roshan roshan   1485 Aug 29 18:49  10.c
-rw-rw-r-- 1 roshan roshan   1545 Aug 29 19:24  11a.c
-rw-rw-r-- 1 roshan roshan   1442 Aug 29 19:25  11b.c
-rw-rw-r-- 1 roshan roshan   1443 Aug 29 19:25  11c.c
-rw-rw-r-- 1 roshan roshan   1934 Aug 29 19:04  12.c
-rw-rw-r-- 1 roshan roshan   1759 Aug 29 19:28  13.c
-rw-rw-r-- 1 roshan roshan   1693 Aug 29 19:22  14.c
-rwxrwxr-x 1 roshan roshan  16056 Aug 29 19:33  15
-rw-rw-r-- 1 roshan roshan    626 Aug 29 19:45  15.c
-rw-rw-r-- 1 roshan roshan      0 Aug 29 19:29  16.c
-rw-r--r-- 1 roshan roshan    790 Aug 27 18:20  1a.c
-rw-rw-rw- 1 roshan roshan    768 Aug 27 18:32  1b.c
-rwxrwxr-x 1 roshan roshan  16040 Aug 27 18:35  1c
-rw-rw-r-- 1 roshan roshan   1291 Aug 27 18:35  1c.c
-rwxrwxr-x 1 roshan roshan  15960 Aug 29 19:45  27a
-rw-rw-r-- 1 roshan roshan    263 Aug 29 19:45  27a.c
-rw-rw-r-- 1 roshan roshan   2262 Aug 29 19:22  2.c
-rw-rw-r-- 1 roshan roshan    831 Aug 29 08:53  3.c
-rw-rw-r-- 1 roshan roshan    900 Aug 29 00:25  4.c
-rw-rw-r-- 1 roshan roshan 108549 Aug 29 19:23  5.c
-rw-rw-r-- 1 roshan roshan    825 Aug 25 00:22  6.c
-rw-rw-r-- 1 roshan roshan   1296 Aug 27 19:12  7.c
-rw-rw-r-- 1 roshan roshan   1049 Aug 29 19:26  8.c
-rwxrwxr-x 1 roshan roshan  16136 Aug 29 08:49  9
-rw-rw-r-- 1 roshan roshan   1745 Aug 29 08:56  9.c
-rw-r--r-- 1 roshan roshan     17 Aug 25 00:23  cp_hello.txt
-rw-rw-r-- 1 roshan roshan     40 Aug 29 00:33  filewrite.txt
-rw-rw-r-- 3 roshan roshan     40 Aug 29 00:35  hardlink
-rwxr--r-- 1 roshan roshan     52 Aug 29 19:02  hello.txt
-rw-r--r-- 1 roshan roshan      0 Aug 25 00:40  my_file.txt
prwx------ 1 roshan roshan      0 Aug 27 18:35  mymkfifo
-rwx------ 1 roshan roshan      0 Aug 27 18:35  mymknod-fifo
drwxrwxr-x 3 roshan roshan   4096 Aug 27 19:14  my-repo
-rwxr--r-- 1 roshan roshan      0 Aug 16 13:16 ' new_file.txt'
-rw------- 1 roshan roshan   2655 Aug 21 18:55  pass_key
-rw-r--r-- 1 roshan roshan    575 Aug 21 18:55  pass_key.pub
-rwxr--r-- 1 roshan roshan     65 Aug 25 00:26  read.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_1.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_2.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_3.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_4.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_5.txt
lrwxrwxrwx 1 roshan roshan      8 Aug 27 18:19  softlink -> test.txt
-rw-rw-r-- 1 roshan roshan     30 Aug 29 00:23 'test (copy).txt'
-rw-rw-r-- 3 roshan roshan     40 Aug 29 00:35  test.txt
*/
