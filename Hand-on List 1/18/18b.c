/*   
============================================================================
Name : 18b.c
Author : Roshan Yadav
Description : Write a program to perform Record locking.
              b. Implement read lock
              Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
Date: 30th Aug, 2024.
============================================================================
*/

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    struct {
        int train_no;
        int ticket_no;
    }db;
        
    int file_desc = open("record.txt",O_RDWR);
    
    struct flock lock;
    int train;
    printf("Enter the train no (1,2,3) :-");
    scanf("%d",&train);
    
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (train-1)*sizeof(db);
    lock.l_pid = getpid();
    
    lseek(file_desc,(train-1)*sizeof(db),SEEK_SET);
    printf("Please wait \n");
    fcntl(file_desc,F_SETLKW,&lock);
    read(file_desc,&db,sizeof(db));
    printf("no of tickets sold is %d\n",db.ticket_no);
    
    lock.l_type = F_UNLCK;
    printf("press Enter to exit\n");
    getchar();
    getchar();
    fcntl(file_desc,F_SETLKW,&lock);
    
    return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 18b.c -o 18b
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./18b
Enter the train no (1,2,3) :-1
Please wait 
no of tickets sold is 4
press Enter to exit

============================================================================
*/


