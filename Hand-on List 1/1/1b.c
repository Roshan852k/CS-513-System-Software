/*  
============================================================================
Name : 1b.c
Author : Roshan Yadav
Description : Create the following types of a files using (i) shell command (ii) system call - hard link (link system call)
Date: 21th Aug, 2024.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>

int main()
{
	int file_desc;
	file_desc=link("test.txt","hardlink");
	if(file_desc==-1)
	{
		printf("Error!");
	}
	else{
	        printf("Hardlink is cretaed successfully\n");
	}
	return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 1b.c -o 1b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./1b
Hardlink is cretaed successfully
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ll hardlink
-rw-rw-r-- 3 roshan roshan 30 Aug 15 20:04 hardlink
============================================================================
*/
