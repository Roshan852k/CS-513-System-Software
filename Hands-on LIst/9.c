/* Name - Roshan Yadav
   Roll No - MT2024169
   
   Problem - Write a program to print the following information about a given file.
            a. inode
            b. number of hard links
            c. uid
            d. uid
            e. size
            f. block size
            g. number of blocks
            h. time of last access
            i. time of last modification
            j. time of last change
*/

#include<stdio.h>
#include<fcntl.h>
#include <sys/stat.h> 
#include<time.h>
void main(){
    int file_status;
    char * file_name = "read.txt";
    
    struct stat file_info;
    
    file_status   = stat(file_name, &file_info);
    
    printf("File Status :-\n");
    printf("inode : %ld\n", file_info.st_ino);
    printf("number of hard links : %ld\n", file_info.st_nlink);
    printf("uid : %d\n", file_info.st_uid);
    printf("uid : %d\n", file_info.st_gid);
    printf("size : %ld\n", file_info.st_size);
    printf("block size : %ld\n", file_info.st_blksize);
    printf("number of blocks :  %ld\n", file_info.st_blocks);
    printf("time of last access : %s", ctime(&file_info.st_atim.tv_sec));
    printf("time of last modification : %s", ctime(&file_info.st_mtim.tv_sec));
    printf("time of last change : %s", ctime(&file_info.st_ctim.tv_sec));
}
 
 /*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 9.c -o 9
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./9
File Status :-
inode : 2643906
number of hard links : 1
uid : 1000
uid : 1000
size : 65
block size : 4096
number of blocks :  8
time of last access : Sun Aug 25 00:26:55 2024
time of last modification : Sun Aug 25 00:26:36 2024
time of last change : Sun Aug 25 00:26:36 2024
*/
	
