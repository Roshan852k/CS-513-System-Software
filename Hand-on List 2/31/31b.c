/*  
============================================================================
Name : 31b.c
Author : Roshan Yadav
Description : Write a program to create a semaphore and initialize value to the semaphore.
              b. create a counting semaphore
Date: 19th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/sem.h> 

void main(){
    union semun {
        int val;
    }sem;
    
    int segKey, semid;

    segKey = ftok(".", 'a'); 
    semid = semget(segKey, 1, IPC_CREAT|0744);
    sem.val = 5;
    semctl(semid, 0, SETVAL, sem);
    
    printf("Counting semaphore created successfully!\n");

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 31b.c -o 31b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./31b
Counting semaphore created successfully!
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x62077d1e 0          roshan     744        1         
0x61077d1e 1          roshan     744        1         

============================================================================
*/ 

