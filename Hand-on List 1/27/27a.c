/*  
============================================================================
Name : 27a.c
Author : Roshan Yadav
Description : Write a program to execute ls -Rl by the following system calls
              a. execl
Date: 28th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

void main(){
      execl("/bin/ls", "ls", "-Rl", NULL);
      return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 27a.c -o 27a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./27a
.:
total 388
-rw-rw-r-- 1 roshan roshan   1507 Aug 30 01:14  10.c
-rw-rw-r-- 1 roshan roshan   1545 Aug 29 19:24  11a.c
-rw-rw-r-- 1 roshan roshan   1442 Aug 29 19:25  11b.c
-rw-rw-r-- 1 roshan roshan   1443 Aug 29 19:25  11c.c
-rw-rw-r-- 1 roshan roshan   1951 Aug 30 01:14  12.c
-rw-rw-r-- 1 roshan roshan   1773 Aug 30 01:14  13.c
-rw-rw-r-- 1 roshan roshan   1728 Aug 30 01:14  14.c
-rw-rw-r-- 1 roshan roshan    659 Aug 30 01:14  15.c
-rw-rw-r-- 1 roshan roshan   1182 Aug 30 13:08  16a.c
-rw-rw-r-- 1 roshan roshan   1183 Aug 30 13:09  16b.c
-rw-rw-r-- 1 roshan roshan    892 Aug 30 01:14  19.c
-rw-r--r-- 1 roshan roshan    790 Aug 27 18:20  1a.c
-rw-rw-rw- 1 roshan roshan    768 Aug 27 18:32  1b.c
-rw-rw-r-- 1 roshan roshan   1291 Aug 27 18:35  1c.c
-rw-rw-r-- 1 roshan roshan    794 Aug 30 01:14  20.c
-rw-rw-r-- 1 roshan roshan    698 Aug 30 01:14  21.c
-rw-rw-r-- 1 roshan roshan   1088 Aug 30 15:43  22.c
-rw-rw-r-- 1 roshan roshan    519 Aug 30 16:07  23.c
-rw-rw-r-- 1 roshan roshan   1010 Aug 30 16:06  24.c
-rwxrwxr-x 1 roshan roshan  16224 Aug 30 16:24  25
-rw-rw-r-- 1 roshan roshan   2108 Aug 30 16:25  25.c
-rwxrwxr-x 1 roshan roshan  15960 Aug 30 17:35  26
-rw-rw-r-- 1 roshan roshan    445 Aug 30 17:39  26.c
-rwxrwxr-x 1 roshan roshan  15960 Aug 30 17:45  27
-rwxrwxr-x 1 roshan roshan  15960 Aug 30 17:58  27a
-rw-rw-r-- 1 roshan roshan   1107 Aug 30 18:03  27a.c
-rwxrwxr-x 1 roshan roshan  15960 Aug 30 18:03  27b
-rw-rw-r-- 1 roshan roshan   2979 Aug 30 18:02  27b.c
-rw-rw-r-- 1 roshan roshan   2985 Aug 30 18:03  27c.c
-rwxrwxr-x 1 roshan roshan  16008 Aug 30 17:56  27d
-rw-rw-r-- 1 roshan roshan   3024 Aug 30 17:57  27d.c
-rw-rw-r-- 1 roshan roshan   2978 Aug 30 13:40  27e.c
-rw-rw-r-- 1 roshan roshan   2244 Aug 30 01:14  2.c
-rw-rw-r-- 1 roshan roshan   1737 Aug 30 15:52  30.c
-rw-rw-r-- 1 roshan roshan    822 Aug 30 01:14  3.c
-rw-rw-r-- 1 roshan roshan    909 Aug 30 13:42  4.c
-rw-rw-r-- 1 roshan roshan 108538 Aug 30 01:14  5.c
-rw-rw-r-- 1 roshan roshan    840 Aug 30 01:14  6.c
-rw-rw-r-- 1 roshan roshan   1301 Aug 30 01:14  7.c
-rw-rw-r-- 1 roshan roshan   1049 Aug 30 01:14  8.c
-rw-rw-r-- 1 roshan roshan   1729 Aug 30 01:14  9.c
-rw-r--r-- 1 roshan roshan     17 Aug 25 00:23  cp_hello.txt
-rw-rw-r-- 1 roshan roshan     40 Aug 29 00:33  filewrite.txt
-rw-rw-r-- 3 roshan roshan     40 Aug 29 00:35  hardlink
-rwxr--r-- 1 roshan roshan     53 Aug 30 13:06  hello.txt
-rw-r--r-- 1 roshan roshan     17 Aug 30 13:06  my_file.txt
prwx------ 1 roshan roshan      0 Aug 27 18:35  mymkfifo
-rwx------ 1 roshan roshan      0 Aug 27 18:35  mymknod-fifo
drwxrwxr-x 3 roshan roshan   4096 Aug 27 19:14  my-repo
-rwxr--r-- 1 roshan roshan      0 Aug 16 13:16 ' new_file.txt'
-rw------- 1 roshan roshan   2655 Aug 21 18:55  pass_key
-rw-r--r-- 1 roshan roshan    575 Aug 21 18:55  pass_key.pub
-rwxr--r-- 1 roshan roshan     65 Aug 25 00:26  read.txt
-rwxr--r-- 1 roshan roshan     29 Aug 30 13:28  sample_1.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_2.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_3.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_4.txt
-rwxr--r-- 1 roshan roshan      0 Aug 25 00:13  sample_5.txt
lrwxrwxrwx 1 roshan roshan      8 Aug 27 18:19  softlink -> test.txt
-rw-rw-r-- 1 roshan roshan     30 Aug 29 00:23 'test (copy).txt'
-rw-rw-r-- 3 roshan roshan     40 Aug 29 00:35  test.txt

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
============================================================================
*/

