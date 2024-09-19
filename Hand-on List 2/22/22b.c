/*  
============================================================================
Name : 22b.c
Author : Roshan Yadav
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 10th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h> 

void main(){
    char buffer[100]; 
    int file_desc  = open("fifo", O_WRONLY);
    if(file_desc==-1){
	    printf("error while source file\n");
    }
    
    printf("Enter the text :");
    scanf(" %[^\n]", buffer);
    write(file_desc, buffer, 100);
    
    close(file_desc);
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 22b.c -o 22b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./22b
Enter the text :Roshan
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./22b
Enter the text :
============================================================================
*/
