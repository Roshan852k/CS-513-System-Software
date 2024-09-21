/*  
============================================================================
Name : 32d.c
Author : Roshan Yadav
Description : Write a program to implement semaphore to protect any critical section.
              d. remove the created semaphore
Date: 20th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h> 

void main(){
    union semun {
        int val;
    }sem;
    
    int segKey, semid, delsemstat;

    segKey = ftok(".", 'b'); 
    semid = semget(segKey, 1, IPC_CREAT|0744);
    
    if (semid == -1)
    {
        perror("Error while creating semaphore!");
    }
    
    delsemstat = semctl(semid, 0, IPC_RMID);
    
    if (semstat == -1)
    {
        perror("failed to delete semaphore!");
    }
    
    printf("Semaphore deleted successfully!\n");

    return;
}
/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 32d.c -o 32d
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./32d
Semaphore deleted successfully!
============================================================================
*/ 

