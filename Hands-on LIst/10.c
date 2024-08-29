/* 
    Name - Roshan Yadav
    Roll No - MT2024169
    Problem - Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
    a. check the return value of lseek
    b . open the file with od and check the empty spaces in between the data.
*/

#include <sys/stat.h>  
#include <fcntl.h>     
#include <sys/types.h> 
#include <unistd.h>    
#include <stdio.h>     

void main()
{
    char *file_name = "test.txt";     
    int file_desc; 
    int offset;         
    int writeByteCount; 

    file_desc = open(file_name, O_RDWR);

    if (file_desc == -1){
        printf("Error while opening file! ");
    }
    else
    {
        offset = lseek(file_desc, 10, SEEK_SET); 
        writeByteCount = write(file_desc, "ABCDEFGHIJ", 10);
        if (writeByteCount == -1)
        {
            perror("Error while writing to the file!");
            _exit(1);
        }

        offset = lseek(file_desc, 10, SEEK_CUR);
        writeByteCount = write(file_desc, "ABCDEFGHIJ", 10);
        if (writeByteCount == -1)
        {
            perror("Error while writing to the file!");
            _exit(1);
        }

        printf("Return value of lseek: %d\n", offset);
        close(file_desc);
    }
    return 0;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 10.c -o 10
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./10
Return value of lseek: 30
*/
