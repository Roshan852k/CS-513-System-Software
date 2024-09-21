/*  
============================================================================
Name : 32c.c
Author : Roshan Yadav
Description : Write a program to implement semaphore to protect any critical section.
              c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 20th Sep, 2024.
============================================================================
*/


#include<sys/ipc.h>   
#include<sys/sem.h>   
#include<sys/types.h> 
#include<sys/shm.h>   
#include<unistd.h>    
#include<stdio.h>    
#include<fcntl.h> 

void main()
{
    char *filename = "./MY/resource.txt"; 
    int fd;   
    ssize_t readBytes;
    off_t lseekOffset;
    char data[1000]; // Sample data

    key_t semKey;   
    int semid;
    int semctlStatus;  
    int semopStatus; 

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error while creating / opening the ticket file!");
        _exit(0);
    }

    // Defines a semaphore's structure
    union semun
    {
        int val;            
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

        semSet.val = 2; // Set a counting semaphore
        semctlStatus = semctl(semid, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = IPC_NOWAIT;

    printf("Press enter to obtain lock for the critical section!\n");
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

    readBytes = read(fd, &data, 1000);
    if (readBytes == -1)
    {
        perror("Error while reading from sample file!");
        _exit(0);
    }
    else if (readBytes == 0)
        printf("No data exists!\n");
    else
        printf("Sample data: \n %s", data);

    printf("Press enter key to exit critical section!\n");
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
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 32c.c -o 32c

Process - 1
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32c
Press enter to obtain lock for the critical section!

Obtained lock on critical section!
Now entering critical section!
No data exists!

Press enter key to exit critical section!


Process - 2
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32c
Press enter to obtain lock for the critical section!

Obtained lock on critical section!
Now entering critical section!
No data exists!

Press enter key to exit critical section!


Process - 3 
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32c
Press enter to obtain lock for the critical section!

Error while operating on semaphore!: Resource temporarily unavailable
============================================================================
*/ 

