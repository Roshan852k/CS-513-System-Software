/* Name - Roshan Yadav
   Roll No - MT2024169
   
   Problem - Write a program to create a file and print the file descriptor value. Use creat ( ) system call
*/

#include<stdio.h>
#include<fcntl.h>
int main(){
	char *fname = "new_file.txt";
	int file_desc = creat(fname, 0744);
	if(file_desc== -1){
	  printf("Error while creating file");
	  return  1;
	}
	printf("File created with file descriptor value : %d\n",file_desc);
        return 0;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 3.c -o 3
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./3
File created with file descriptor value : 3
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ll new_file.txt
-rwxr--r-- 1 roshan roshan 0 Aug 24 23:59 new_file.txt*
*/
