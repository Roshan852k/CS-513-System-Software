/*  
============================================================================
Name : 4.c
Author : Roshan Yadav
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 21th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h> 
#include<errno.h>  

int main(){	
      char *file_name = "my_file.txt";
      int file_desc = open(file_name, O_CREAT | O_RDWR | O_EXCL, 0644);
      if(file_desc==-1){
	      perror("Error in opening file\n");
      }
      else{
	      printf("File open successfully\n");
      }
      close(file_desc);
      return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 4.c -o 4
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./4
Error in opening file
: File exists
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ll my_file.txt
-rw-r--r-- 1 roshan roshan 0 Aug 25 00:40 my_file.txt
============================================================================
*/

