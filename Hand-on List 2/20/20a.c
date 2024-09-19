/*  
============================================================================
Name : 20a.c
Author : Roshan Yadav
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
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
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 20a.c -o 20a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./20a
Enter the text : pipeline is working
============================================================================
*/
