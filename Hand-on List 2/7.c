/*  
============================================================================
Name : 7.c
Author : Roshan Yadav
Description : Write a simple program to print the created thread ids.
Date: 9th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<pthread.h>

void *sampleFunction(void *data)
{
    printf("Thread id is: %lu\n", pthread_self());
}

void main(){
 
    pthread_t thread;

    if (pthread_create(&thread, NULL, sampleFunction, NULL))
        perror("Error while creating thread one");
    else
        printf("Thread is created\n");
        
    pthread_join(threadOne, NULL);

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 7.c -o 7
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./7
Thread is created
Thread id is: 140291428316864
============================================================================
*/
