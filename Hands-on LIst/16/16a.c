/* 
============================================================================
Name : 16a.c
Author : Roshan Yadav
Description : Write a program to perform mandatory locking.
              a. Implement write lock
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

    lock.l_type = F_WRLCK;    
    lock.l_whence = SEEK_SET; 
    lock.l_start = 0;         
    lock.l_len = 0;           
    lock.l_pid = getpid();
    lockStatus = lock;

    file_desc = open(file_name, O_RDWR);

    fcntl(file_desc, F_GETLK, &lockStatus);

    if (lockStatus.l_type == F_WRLCK){
        printf("File already has a write lock\n");
        getchar();
    }
    if (lockStatus.l_type == F_RDLCK){
        printf("File already has a read lock\n");
    }
 
    fcntl(file_desc, F_SETLK, &lock);
    printf("File is now locked for writing\n");
    getchar();

    close(file_desc);
}

/*
============================================================================
Process 1:
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 16a.c -o 16a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./16a
File is now locked for writing

Process 2:
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./16a
File is now locked for writing

============================================================================
*/


