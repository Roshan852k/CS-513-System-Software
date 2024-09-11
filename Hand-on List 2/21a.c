/*  
============================================================================
Name : 20a.c
Author : Roshan Yadav
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 10th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h> 

void main(){
    char buffer1[50], buffer2[50]; 
    int file_desc_1  = open("fifo1", O_WRONLY);
    int file_desc_2  = open("fifo2", O_RDONLY);
    
    if(file_desc_1==-1 || file_desc_2==-1 ){
	    printf("error while opening file\n");
    }
    
    printf("Enter the text :");
    scanf(" %[^\n]", buffer1);
    write(file_desc_1, buffer1, 50);
    
    read(file_desc_2, buffer2, 50);
    printf("The text from the FIFO : %s\n", buffer2);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 21a.c -o 21a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./21a
Enter the text : Hello
The text from the FIFO : Hii
============================================================================
*/
