/*  
============================================================================
Name : 6.c
Author : Roshan Yadav
Description : Write a simple program to create three threads.
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
 
    pthread_t threadOne, threadTwo, threadThree;

    if (pthread_create(&threadOne, NULL, sampleFunction, NULL))
        perror("Error while creating thread one");
    if (pthread_create(&threadTwo, NULL, sampleFunction, NULL))
        perror("Error while creating thread two");
    if (pthread_create(&threadThree, NULL, sampleFunction, NULL))
        perror("Error while creating thread three");
    
    pthread_join(threadOne, NULL);
    pthread_join(threadTwo, NULL);
    pthread_join(threadThree, NULL);

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 6.c -o 6
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./6
Thread id is: 140047540025024
Thread id is: 140047531632320
Thread id is: 140047523239616
============================================================================
*/
