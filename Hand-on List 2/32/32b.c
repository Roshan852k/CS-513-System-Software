/*  
============================================================================
Name : 32b.c
Author : Roshan Yadav
Description : Write a program to implement semaphore to protect any critical section.
              b. protect shared memory from concurrent write access
Date: 20th Sep, 2024.
============================================================================
*/

#include<sys/ipc.h>   
#include<sys/sem.h>   
#include<sys/types.h> 
#include<sys/shm.h>   
#include<unistd.h>    
#include<stdio.h>     

void main()
{
    key_t semKey;      
    int semid; 
    int semctlStatus;  
    int semopStatus; 
    
    key_t shmKey;        
    int shmid;    
    ssize_t shmSize = 20; 
    char *shmPointer;

    // Defines a semaphore's structure
    union semun
    {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf;
    } semSet;

    semKey = ftok(".", 3321);
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

    shmKey = ftok(".", 'a');

    if (shmKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    shmid = shmget(shmKey, shmSize, IPC_CREAT | 0700); 

    if (shmid == -1)
    {
        perror("Error while getting Shared Memory!");
        _exit(0);
    }

    shmPointer = shmat(shmid, 0, 0);

    if (*shmPointer == -1)
    {
        perror("Error while attaching address space!");
        _exit(0);
    }

    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to lock the critical section!\n");
    getchar();
    
    // Use semaphore to lock the critical section
    semOp.sem_op = -1;
    semopStatus = semop(semid, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    
    printf("Critical Section is now locked!\n");

    printf("Start of the critical section!\n");
    
    // Writing to the shared memory
    printf("Enter the text: ");
    scanf("%[^\n]", shmPointer);

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Text from shared memory: %s\n", shmPointer);

    printf("Press enter to exit the critical section!\n");
    getchar();

    // Use semaphore to unlock the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semid, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    printf("Critical section is now unlocked!\n");
    
    return ;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 32b.c -o 32b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32b
Press enter to lock the critical section!

Critical Section is now locked!
Start of the critical section!
Enter the text: Hello
Press enter to read from the shared memory!
Text from shared memory: Hello
Press enter to exit the critical section!

Critical section is now unlocked!

============================================================================
*/ 

