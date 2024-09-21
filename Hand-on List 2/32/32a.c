/*  
============================================================================
Name : 32a.c
Author : Roshan Yadav
Description : Write a program to implement semaphore to protect any critical section.
              a. rewrite the ticket number creation program using semaphore
Date: 20th Sep, 2024.
============================================================================
*/

#include<sys/ipc.h>   
#include<sys/sem.h>   
#include<sys/types.h> 
#include<sys/stat.h> 
#include<fcntl.h>    
#include<unistd.h>   
#include<stdio.h>     

void main()
{
    char *ticketFile = "./MY/ticket.txt"; 
    int fd;            
    ssize_t readBytes, writeBytes; 
    off_t lseekOffset;
    int data; // Ticket data

    key_t semKey;      
    int semid; 
    int semctlStatus;  
    int semopStatus; 
    
    fd = open(ticketFile, O_CREAT | O_RDWR, S_IRWXU);
    
    if (fd == -1)
    {
        perror("Error while creating / opening the ticket file!");
        _exit(0);
    }

    // Defines a semaphore's structure
    union semun
    {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf;
    } semSet;

    semKey = ftok(".", 'a');
    
    if (semKey == -1)
    {
        perror("Error while computing key!");
        _exit(1);
    }

    semid = semget(semKey, 1, 0); 
    if (semid == -1)
    {
        semid = semget(semKey, 1, IPC_CREAT | 0700); 
        if (semid == -1)
        {
            perror("Error while creating semaphore!");
            _exit(1);
        }

        semSet.val = 1; // Set a binary semaphore
        semctlStatus = semctl(semid, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf semOp; // Defines the operation on the semaphore
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to obtain lock on the critical section\n");
    getchar();
    
    // Use semaphore to lock the critical section
    semOp.sem_op = -1;
    semopStatus = semop(semid, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    
    printf("Obtained lock on critical section!\n");
    printf("Now entering critical section!\n");

    readBytes = read(fd, &data, sizeof(data));
    if (readBytes == -1)
    {
        perror("Error while reading from ticket file!");
        _exit(0);
    }
    else if (readBytes == 0) 
        data = 1;
    else
    {
        data += 1;
        lseekOffset = lseek(fd, 0, SEEK_SET);
        if (lseekOffset == -1)
        {
            perror("Error while seeking!");
            _exit(0);
        }
    }

    writeBytes = write(fd, &data, sizeof(data));
    if (writeBytes == -1)
    {
        perror("Error while writing to ticket file!");
        _exit(1);
    }

    printf("Your ticker number is - %d\n", data);

    printf("Press enter to exit from critical section!\n");
    getchar();

    // Use semaphore to unlock the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semid, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    close(fd);
    
    return ;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 32a.c -o 32a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32a
Press enter to obtain lock on the critical section

Obtained lock on critical section!
Now entering critical section!
Your ticker number is - 1
Press enter to exit from critical section!

roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32a
Press enter to obtain lock on the critical section

Obtained lock on critical section!
Now entering critical section!
Your ticker number is - 2
Press enter to exit from critical section!

============================================================================
*/ 

