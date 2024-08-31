/* 
    Name - Roshan Yadav
    Roll No - MT2024169
    Problem - Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate         program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
*/

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
    char * ticketfile = "ticket_record.txt";
    int file_desc =  open(ticketfile, O_CREAT|O_RDWR, S_IRWXU, 0644);
    int buffer=0;
   
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_start = 0;
    
    int fcntlstatus = fcntl(file_desc,F_GETLK,&lock);
    if (fcntlstatus == -1)
        printf("Error while getting lock status!");
    else
    {
        if(lock.l_type==F_RDLCK)
            printf("file already locked for reading");
        else if(lock.l_type==F_WRLCK)
            printf("file already locked for writing");
        else
        {
           lock.l_type = F_WRLCK;
           fcntl(file_desc,F_SETLKW,&lock);
           int readbytes=read(file_desc,&buffer,sizeof(int));
           if(readbytes==-1)
           {
             printf("Error while reading the file!\n");
             return 0;
           }
           if(readbytes==0)
           {
              buffer=1;
              write(file_desc,&buffer,sizeof(int));
              printf("Your ticket number is: %d\n", buffer);
           }
           else
           {
              lseek(file_desc,0,SEEK_SET);
              read(file_desc,&buffer,sizeof(int));
              buffer+=1;
              write(file_desc,&buffer,sizeof(int));
              printf("Your ticket number is: %d\n", buffer);
           }
           printf("Press Enter to complete the transaction");
           char c = getchar();
           if(c)
           {
                lock.l_type = F_UNLCK;
                int fcntlStatus = fcntl(file_desc, F_SETLKW, &lock);
                if (fcntlStatus == -1)
                    perror("Error releasing lock!");
                else
                    printf("Done!\n"); 
           }
                               
        }
    }
    close(file_desc);
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 17.c -o 17
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./17
Your ticket number is: 1
Press Enter to complete the transaction
Done!

roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./17
Your ticket number is: 2
Press Enter to complete the transaction
Done!

*/
