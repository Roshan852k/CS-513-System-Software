/*  
============================================================================
Name : 24.c
Author : Roshan Yadav
Description : Write a program to create a message queue and print the key and message queue id.
Date: 18th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

void main(){
    int key = ftok(".", 'a');
    int msgid = msgget(key, IPC_CREAT|IPC_EXCL|0744);
    printf("key = 0x%0x\n", key);
    printf("Message queue Id = %d\n", msgid);
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 24.c -o 24
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./24
key = 0x61077d1e
Message queue Id = 0
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x62077d1e 1          roshan     744        0            0 
============================================================================
*/ 

