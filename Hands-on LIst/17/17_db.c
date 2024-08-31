/*  
============================================================================
Name : 17.c
Author : Roshan Yadav
Description : Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate         program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
Date: 30th Aug, 2024.
============================================================================
*/

#include<unistd.h>    
#include<fcntl.h>     
#include<sys/types.h> 
#include<sys/stat.h>  
#include<stdio.h>     

int main() {
    int file_desc;
    struct {
        int ticket_no;
    } db;

    db.ticket_no = 10;
    file_desc = open("db", O_CREAT | O_RDWR, 0744);
    if (file_desc == -1) {
        perror("Error opening file");
        return 1;
    }

    write(file_desc, &db, sizeof(db));
    close(file_desc);

    file_desc = open("db", O_RDONLY);

    read(file_desc, &db, sizeof(db));
    printf("Ticket no: %d\n", db.ticket_no); 
    close(file_desc);
    return 0;
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 17a.c -o 17a
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./17a
Ticket no: 10
============================================================================
*/
