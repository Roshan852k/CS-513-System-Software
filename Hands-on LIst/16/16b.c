/* 
============================================================================
Name : 16b.c
Author : Roshan Yadav
Description : Write a program to perform mandatory locking.
              b. Implement read lock
Date: 25th Aug, 2024.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>    
#include<fcntl.h>     
#include<sys/types.h> 
#include<sys/stat.h>  

void main()
{
    char *file_name = "my_file.txt";
    struct flock lock, lockStatus;
    int file_desc;

    lock.l_type = F_RDLCK;    
    lock.l_whence = SEEK_SET; 
    lock.l_start = 0;         
    lock.l_len = 0;           
    lock.l_pid = getpid();
    lockStatus = lock;

    file_desc = open(file_name, O_RDONLY);

    fcntl(file_desc, F_GETLK, &lockStatus);

    if (lockStatus.l_type == F_WRLCK){
        printf("File already has a write lock\n");
        getchar();
    }

    fcntl(file_desc, F_SETLK, &lock);
    printf("File is now locked for reading\n");
    getchar();

    close(file_desc);
}

/*
============================================================================
Process 1:
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 16b.c -o 16b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./16b
File is now locked for reading

Process 2:
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./16b
File is now locked for reading

============================================================================
*/

