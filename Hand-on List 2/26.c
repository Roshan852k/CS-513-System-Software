/*  
============================================================================
Name : 26.c
Author : Roshan Yadav
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 18th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>

void main(){
    struct msg {
      long int m_type;
      char message[80];
    } myq;
    
    int key = ftok(".", 'a');
    int mqid = msgget(key, IPC_CREAT | 0666);
    //int mqid = 1;
    
    printf("Enter message type: ");
    scanf("%ld", &myq.m_type);
    getchar();            // Clear newline from input buffer
    printf("Enter message text: ");
    scanf(" %[^\n]", myq.message);
    
    int size = strlen(myq.message);
    int stat = msgsnd(mqid, &myq, size + 1, 0);
    if (stat == -1) {
        perror("Failed");
        return ;
    }
    printf("Message sent successfully.\n");
    
    return;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 26.c -o 26
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./26
Enter message type: 1
Enter message text: Hello Roshan
Message sent successfully.
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x62077d1e 1          roshan     744        13           1 
      
============================================================================
*/ 

