/* 
    Name - Roshan Yadav
    Roll No - MT2024169
    Problem - Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(){
    struct 
    {
        int train_no;
        int ticket_no;
    }db[3];
    
    for(int i=0;i<3;i++)
    {
        db[i].train_no=i+1;
        db[i].ticket_no=0;
    }
    
    int fd=open("record.txt",O_CREAT|O_RDWR,0777);
    write(fd,db,sizeof(db));
}
