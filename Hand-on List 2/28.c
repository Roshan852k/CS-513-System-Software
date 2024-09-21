/*  
============================================================================
Name : 28.c
Author : Roshan Yadav
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    
    msgctlStatus = msgctl(msgid, IPC_STAT, &messageQueueInfo);
    printf("Press enter to change the permissions!\n");
    getchar();

    messageQueueInfo.msg_perm.mode = 0777;
    msgctlStatus = msgctl(msgid, IPC_SET, &messageQueueInfo);
    
    if(msgctlStatus == -1){
        perror("Error while changing permission of Message Queue");
    }
    printf("Permissions change successfully!\n");

    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 28.c -o 28
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./28
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61077d1e 0          roshan     744        0            0           
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./28
key = 0x61077d1e
Message queue Id = -1
Press enter to change the permissions!

Permissions change successfully!
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61077d1e 1          roshan     777        0            0                  
============================================================================
*/ 

