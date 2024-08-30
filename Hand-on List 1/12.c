/* 
    Name - Roshan Yadav
    Roll No - MT2024169
    Problem - Write a program to find out the opening mode of a file. Use fcntl.
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

void main(){
    char * file = "hello.txt";
    int file_mode;
    int file_desc   = open(file, O_WRONLY);
    
    if(file_desc==-1){
	    printf("error while opening file\n");
    }
    
    file_mode = fcntl(file_desc, F_GETFL);

    switch (file_mode & O_ACCMODE) {
        case 0:
            printf("The file is opened in read-only mode\n");
            break;
        case 1:
            printf("The file is opened in write-only mode\n");
            break;
        case 2:
            printf("The file is opened in read-write mode\n");
            break;
        case 64:
            printf("The file has been opened with the flags : O_CREAT\n");
            break;
        case 512:
            printf("The file has been opened with the flags : O_TRUNC\n");
            break;
        case 1024:
            printf("The file has been opened with the flags : O_APPEND\n");
            break;
        case 577:
            printf("The file has been opened with the flags : O_WRONLY | O_CREAT | O_TRUNC\n");
            break;
        case 1089:
            printf("The file has been opened with the flags : O_WRONLY | O_CREAT | O_APPEND\n");
            break;
        case 578:
            printf("The file has been opened with the flags : O_RDWR   | O_CREAT | O_TRUNC\n");
            break;
        case 1090:
            printf("The file has been opened with the flags : O_RDWR   | O_CREAT | O_APPEND\n");
            break;
        default:
            printf("Erorr\n"); 
    }
    
    close(file_desc);
    return 0;
}


/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 12.c -o 12
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./12
The file is opened in write-only mode
*/
