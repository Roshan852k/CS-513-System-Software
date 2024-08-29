/* 
    Name - Roshan Yadav
    Roll No - MT2024169
    Problem - Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
*/

#include<stdio.h> 
#include<fcntl.h>
#include<unistd.h>

void main(){
    char *buffer[1]; 
    int CountSourcRead;
    char * file_name = "read.txt";
    int file_desc   = open(file_name, O_RDONLY);
    if(file_desc==-1){
	    printf("error while opening file\n");
    }
    while ((CountSourcRead = read(file_desc, buffer, 1)) == 1)
    {
        write(STDOUT_FILENO, buffer, 1);
    }
    close(file_desc);
    return 0;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cat read.txt
I am Roshan Yadav
Doing Mtech from IIITB
Learning LInux Commnad 
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 8.c -o 8
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./8
I am Roshan Yadav
Doing Mtech from IIITB
Learning LInux Commnad 
*/
	
