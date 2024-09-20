/*  
============================================================================
Name : 25.c
Author : Roshan Yadav
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
              a. access permission
              b. uid, gid
              c. time of last message sent and received
              d. time of last change in the message queue
              d. size of the queue
              f. number of messages in the queue
              g. maximum number of bytes allowed
              h. pid of the msgsnd and msgrcv
Date: 18th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

void main(){             
    struct msqid_ds messageQueueInfo; 
    int msgctlStatus;                 
    
    int key = ftok(".", 'a');
    int msgid = msgget(key, IPC_CREAT|0744);
    
    printf("Key: 0x%0x\n", key);
    printf("Message queue Id : %d\n", msgid);

    msgctlStatus = msgctl(msgid, IPC_STAT, &messageQueueInfo);

    printf("Access Permission: %od\n", messageQueueInfo.msg_perm.mode);
    printf("UID: %d\n", messageQueueInfo.msg_perm.uid);
    printf("GID: %d\n", messageQueueInfo.msg_perm.gid);
    printf("Time of last message sent: %ld\n", messageQueueInfo.msg_stime);
    printf("Time of last message received: %ld\n", messageQueueInfo.msg_rtime);
    printf("Size of queue: %ld\n", messageQueueInfo.__msg_cbytes);
    printf("Number of messages in the queue: %ld\n", messageQueueInfo.msg_qnum);
    printf("Maximum number of bytes allowed in the queue: %ld\n", messageQueueInfo.msg_qbytes);
    printf("PID of last sent message: %d\n", messageQueueInfo.msg_lspid);
    printf("PID of last received message: %d\n", messageQueueInfo.msg_lrpid);
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 25.c -o 25
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./25
Key: 0x61077d1e
Message queue Id : 2
Access Permission: 744d
UID: 1000
GID: 1000
Time of last message sent: 0
Time of last message received: 0
Size of queue: 0
Number of messages in the queue: 0
Maximum number of bytes allowed in the queue: 16384
PID of last sent message: 0
PID of last received message: 0
============================================================================
*/ 

