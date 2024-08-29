/* Name - Roshan Yadav
   Roll No - MT2024169
   
   Problem - Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
verify whether the data is available within 10 seconds or not (check in $man 2 select).
*/

#include <sys/time.h>  
#include <sys/types.h> 
#include <unistd.h>    
#include <stdio.h>     

void main()
{
    fd_set readFDSet, writeFDSet;
    struct timeval time;
    int returnVal;


    FD_SET(STDIN_FILENO, &readFDSet);   
    FD_SET(STDOUT_FILENO, &writeFDSet);

    time.tv_sec = 10;
    time.tv_usec = 0;

    returnVal = select(1, &readFDSet, &writeFDSet, NULL, &time);

    if (returnVal == -1){
        perror("ERROR");
    }
    else if (returnVal){
        printf("The data is now available\n");
    }
    else{
        printf("No data was given for 10 seconds\n");
    }
}
	
/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 13.c -o 13
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./13
ls
The data is now available
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ls
 10.c    11c.c   13.c   15.c   1c     27a.c   4.c   7.c   9.c             hardlink      mymkfifo      ' new_file.txt'   read.txt       sample_3.txt   softlink
 11a.c   12.c    14     1a.c   1c.c   2.c     5.c   8.c   cp_hello.txt    hello.txt     mymknod-fifo   pass_key         sample_1.txt   sample_4.txt  'test (copy).txt'
 11b.c   13      14.c   1b.c   27     3.c     6.c   9     filewrite.txt   my_file.txt   my-repo        pass_key.pub     sample_2.txt   sample_5.txt   test.txt
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./13
No data was given for 10 seconds
*/
