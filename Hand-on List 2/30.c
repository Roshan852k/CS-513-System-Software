/*  
============================================================================
Name : 30.c
Author : Roshan Yadav
Description : Write a program to create a shared memory.
              a. write some data to the shared memory
              b. attach with O_RDONLY and check whether you are able to overwrite.
              c. detach the shared memory
              d. remove the shared memory
Date: 19th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>  
#include<signal.h>

/*
void signal_handler(int signum) {
    printf("Caught segmentation fault : Due to try write in read-only memory.\n");
    return;
}
*/

void main(){
    char *shmPointer, *rdOnlyShmPointer;
    int shmKey, shmid;
    
    // signal(SIGSEGV, signal_handler);
    
    shmKey = ftok(".", 'b');
    
    shmid = shmget(shmKey, 1024, IPC_CREAT|0744);
    shmPointer = shmat(shmid, 0, 0);
    
    printf("Enter the text: ");
    scanf("%[^\n]", shmPointer);
    
    shmPointer = shmat(shmid, 0, 0);
    printf("Text from shared memory: %s\n", shmPointer);
    getchar();
    
    //rdOnlyShmPointer = shmat(shmid, 0, SHM_RDONLY);
    //sprintf(rdOnlyShmPointer, "Overwrite"); 
    //printf("Text from shared memory: %s\n", rdOnlyShmPointer);

    shmdt(shmPointer);       // Dettach pointer to Shared Memory
    printf("Dettach pointer to Shared Memory successfully!\n");
    
    shmctl(shmid, IPC_RMID, NULL);
    printf("remove the shared memory successfully!\n");

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 30.c -o 30
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./30
Enter the text: Hello Roshan
Text from shared memory: Hello Roshan
Dettach pointer to Shared Memory successfully!
remove the shared memory successfully!
============================================================================
*/ 

