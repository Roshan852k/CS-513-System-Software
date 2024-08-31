/* 
    Name - Roshan Yadav
    Roll No - MT2024169
    Problem - Write a program to perform Record locking.
              a. Implement write lock
              Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
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
    
    struct flock lock;
    int train;
    
    int file_desc = open("record.txt",O_RDWR);
    
    printf("Enter the train no (1,2,3) :-");
    scanf("%d",&train);
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (train-1)*sizeof(db);
    lock.l_pid = getpid();
    
    lseek(file_desc,(train-1)*sizeof(db),SEEK_SET);
    printf("Please wait \n");
    fcntl(file_desc,F_SETLKW,&lock);
    read(file_desc,&db,sizeof(db));
    printf("no of tickets sold is %d\n",db.ticket_no);
    
    db.ticket_no++;
    lseek(file_desc,-1*sizeof(db),SEEK_CUR);  
    
    lock.l_type = F_UNLCK;
    printf("press Enter to book ticket\n");
    getchar();
    getchar();
    printf("Your ticket no is %d\n",db.ticket_no);
    write(file_desc,&db,sizeof(db));
    fcntl(file_desc,F_SETLKW,&lock);
    
    return 0;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 18a.c -o 18a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./18a
Enter the train no (1,2,3) :-1
Please wait 
no of tickets sold is 3
press Enter to book ticket

Your ticket no is 4
*/
