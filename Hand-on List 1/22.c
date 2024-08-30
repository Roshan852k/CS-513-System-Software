/* 
    Name - Roshan Yadav
    Roll N0 - MT2024169
    Problem - Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/stat.h> 

void main()
{
    char *file_name = "sample_1.txt";
    int childPid, file_desc;
    file_desc = open(file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

    if ((childPid = fork()) != 0){
        write(file_desc, "Parent Process\n!", 15);
    }
    else{
        write(file_desc, "Child Process\n!", 14);
    }
    close(file_desc);
    return ;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cat sample_1.txt
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 22.c -o 22
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./22
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cat sample_1.txt
Parent Process
Child Process
*/

