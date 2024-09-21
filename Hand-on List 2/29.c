/*  
============================================================================
Name : 29.c
Author : Roshan Yadav
Description : Write a program to remove the message queue.
Date: 19th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

void main(){
    int key = ftok(".", 'a');
    int msgid = msgget(key, IPC_CREAT|0744);
    printf("key = 0x%0x\n", key);
    printf("Message queue Id = %d\n", msgid);
    
    struct msqid_ds messageQueueInfo;
    int msgctlStatus;
    
    msgctlStatus = msgctl(msgid, IPC_RMID, NULL);
    
    if(msgctlStatus == -1){
        perror("Error while removing message queue");
    }
    printf("Message queue removed successfully!\n");

    return;
}


/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 29.c -o 29
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./29
key = 0x61077d1e
Message queue Id = 3
Message queue removed successfully!
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

============================================================================
*/ 

