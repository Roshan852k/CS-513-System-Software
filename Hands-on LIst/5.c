/*   
============================================================================
Name : 5.c
Author : Roshan Yadav
Description : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 21th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>

int main(){
	char *fname1 = "sample_1.txt";
	char *fname2 = "sample_2.txt";
	char *fname3 = "sample_3.txt";
	char *fname4 = "sample_4.txt";
	char *fname5 = "sample_5.txt";
	while(1){
		int file_desc_1 = creat(fname1,0744);
		int file_desc_2 = creat(fname2,0744);
		int file_desc_3 = creat(fname3,0744);
		int file_desc_4 = creat(fname4,0744);
		int file_desc_5 = creat(fname5,0744);
	}      
    return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 5.c -o 5
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./5
^C  
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./5 &
[3] 11775
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cd /proc/11775/fd
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:/proc/11775/fd$ ll
total 0
dr-x------ 2 roshan roshan 1024 Aug 25 00:14 ./
dr-xr-xr-x 9 roshan roshan    0 Aug 25 00:14 ../
lrwx------ 1 roshan roshan   64 Aug 25 00:14 0 -> /dev/pts/0
lrwx------ 1 roshan roshan   64 Aug 25 00:14 1 -> /dev/pts/0
l-wx------ 1 roshan roshan   64 Aug 25 00:14 10 -> /home/roshan/Software_System/hand-on-1/sample_3.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 100 -> /home/roshan/Software_System/hand-on-1/sample_3.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1000 -> /home/roshan/Software_System/hand-on-1/sample_3.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1001 -> /home/roshan/Software_System/hand-on-1/sample_4.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1002 -> /home/roshan/Software_System/hand-on-1/sample_5.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1003 -> /home/roshan/Software_System/hand-on-1/sample_1.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1004 -> /home/roshan/Software_System/hand-on-1/sample_2.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1005 -> /home/roshan/Software_System/hand-on-1/sample_3.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1006 -> /home/roshan/Software_System/hand-on-1/sample_4.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1007 -> /home/roshan/Software_System/hand-on-1/sample_5.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1008 -> /home/roshan/Software_System/hand-on-1/sample_1.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1009 -> /home/roshan/Software_System/hand-on-1/sample_2.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 101 -> /home/roshan/Software_System/hand-on-1/sample_4.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1010 -> /home/roshan/Software_System/hand-on-1/sample_3.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1011 -> /home/roshan/Software_System/hand-on-1/sample_4.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1012 -> /home/roshan/Software_System/hand-on-1/sample_5.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1013 -> /home/roshan/Software_System/hand-on-1/sample_1.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1014 -> /home/roshan/Software_System/hand-on-1/sample_2.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1015 -> /home/roshan/Software_System/hand-on-1/sample_3.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1016 -> /home/roshan/Software_System/hand-on-1/sample_4.txt*
l-wx------ 1 roshan roshan   64 Aug 25 00:14 1017 -> /home/roshan/Software_System/hand-on-1/sample_5.txt*
^c
============================================================================
*/

