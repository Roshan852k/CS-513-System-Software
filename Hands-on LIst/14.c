/* Name - Roshan Yadav
   Roll No - MT2024169
   
   Problem - Write a program to find the type of a file.
             a. Input should be taken from command line.
             b. program should be able to identify any type of a file.
*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h> 
#include<sys/stat.h>  
#include<stdlib.h>

void main(int argc, char *argv[]){
  char *file_name = argv[1];
  int file_desc;
  struct stat statbuf;
  
  if(argc!=2){
    printf("File name not pass as argument\n");
    exit(0);
  }
  
  file_desc = open(file_name, O_RDONLY);
  if(file_desc==-1){
        perror("Error in opening file\n");
  }
  
  fstat(file_desc, &statbuf);
  
  
  if (S_ISREG(statbuf.st_mode))
      write(STDOUT_FILENO, "Regular File\n", 13);

  else if (S_ISDIR(statbuf.st_mode))
      write(STDOUT_FILENO, "Directory File\n", 15);

  else if (S_ISCHR(statbuf.st_mode))
      write(STDOUT_FILENO, "Character File\n", 15);

  else if (S_ISBLK(statbuf.st_mode))
      write(STDOUT_FILENO, "Block File\n", 11);

  else if (S_ISFIFO(statbuf.st_mode))
      write(STDOUT_FILENO, "FIFO File\n", 10);

  else if (S_ISLNK(statbuf.st_mode))
      write(STDOUT_FILENO, "Symbolic Link File\n", 19);

  else if (S_ISSOCK(statbuf.st_mode))
      write(STDOUT_FILENO, "Socket\n", 7);

  else
      write(STDOUT_FILENO, "Error\n", 6);
  return;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 14.c -o 14
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./14
File name not pass as argumnet
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./14 hello.txt
Regular File
*/
