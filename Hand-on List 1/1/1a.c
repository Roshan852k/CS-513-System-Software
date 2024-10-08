/*   
============================================================================
Name : 1a.c
Author : Roshan Yadav
Description : Create the following types of a files using (i) shell command (ii) system call - soft link(symlink system call)
Date: 21th Aug, 2024.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>

int main() 
{
	int file_desc;
	file_desc=symlink("test.txt","softlink");
	if(file_desc==-1)
	{
		printf("Error!\n");
	}
	else{
	        printf("Softlink is cretaed successfully\n");
	}
	return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 1a.c -o 1a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./1a
Softlink is cretaed successfully
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ll softlink
lrwxrwxrwx 1 roshan roshan 8 Aug 27 18:19 softlink -> test.txt
============================================================================
*/



