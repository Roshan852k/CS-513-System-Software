/*   
============================================================================
Name : 11c.c
Author : Roshan Yadav
Description : Write a program to open a file, duplicate the file descriptor and append the file with both thedescriptors and check whether the file is updated properly or not. 
            - use fcntl
Date: 23th Aug, 2024.
============================================================================
*/

#include<stdio.h> 
#include<fcntl.h>
#include<sys/stat.h> 
#include<unistd.h>    
#include<sys/types.h> 

void main()
{
    char *fname = "hello.txt";                      
    int file_desc, dup_file_desc; 
    int CountDestinationWrite;     


    file_desc = open(fname, O_WRONLY | O_APPEND);
    if (file_desc == -1){
        perror("error while opening file\n");
    }
    else
    {
        dup_file_desc =  fcntl(file_desc,F_DUPFD);

        CountDestinationWrite = write(file_desc, "Using original FD ", 17);
        if (CountDestinationWrite == -1)
            perror("error while writing file using original FD\n");

        CountDestinationWrite = write(dup_file_desc, "Using duplicate FD", 18);
        if (CountDestinationWrite == -1)
            perror("Error while writing file using duplicate FD\n");

        close(file_desc);
    }
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 11c.c -o 11c
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./11c
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cat hello.txt
Welcome to Linux
Using original FDUsing duplicate FD
============================================================================
*/