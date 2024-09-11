/*  
============================================================================
Name : 20b.c
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
    int file_desc  = open("fifo", O_RDONLY);
    if(file_desc==-1){
	    printf("error while opening file\n");
    }
    
    read(file_desc, buffer, 100);
    printf("The text from the FIFO : %s\n", buffer);
    
    close(file_desc); 
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 20b.c -o 20b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./20b
The text from the FIFO : pipeline is working
============================================================================
*/

