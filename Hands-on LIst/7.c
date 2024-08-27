/* Name - Roshan Yadav
   Roll No - MT2024169
   
   Problem - Write a program to copy file1 into file2
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

void main(){
    char *buffer[100]; 
    int CountSourcRead, CountDestinationWrite;
    char* src_file = "hello.txt";
    char* dest_file = "cp_hello.txt";
    
    int src_file_desc   = open(src_file, O_RDONLY);
    if(src_file_desc==-1){
	    printf("error while opening source file\n");
    }
    
    int dest_file_desc   = open(dest_file, O_WRONLY | O_CREAT, 0644);
    if(dest_file_desc==-1){
	    printf("error while opening destination file\n");
    }
    
    while ((CountSourcRead = read(src_file_desc, buffer, 100)) > 0)
    {
        write(dest_file_desc, buffer, CountSourcRead);   
    }
    printf("data copy sucessfully\n");
    
    close(src_file_desc);
    close(dest_file_desc);
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 7.c -o 7
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./7
data copy sucessfully
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cat hello.txt
Welcome to Linux
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cat cp_hello.txt
Welcome to Linux

*/
	
