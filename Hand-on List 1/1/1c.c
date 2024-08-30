/*  
	Name - Roshan Yadav
	Roll No - MT2024169 
	Problem - Create the following types of a files using (i) shell command (ii) system call - FIFO (mkfifo Library Function or mknod system call)
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
	char *mkfifoName = "./mymkfifo";    
	char *mknodName = "./mymknod-fifo"; 

	int mkfifo_stat = mkfifo(mkfifoName, S_IRWXU);
	if(mkfifo_stat == -1){
		printf("Error during creating pipe using mkfifo\n");
	}
	else{
		printf("pipe created successfully using mkfifo\n");
	}

	int mknod_stat = mknod(mknodName, S_IRWXU, 0);
	if(mknod_stat == -1){
		printf("Error during creating pipe using mknod\n");
	}
	else{
		printf("pipe created successfully using mknod\n");
	}
	return 0;
}

/*
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 1c.c -o 1c
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./1c
pipe created successfully using mkfifo
pipe created successfully using mknod
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ll mymkfifo mymknod-fifo
prwx------ 1 roshan roshan 0 Aug 27 18:35 mymkfifo|
-rwx------ 1 roshan roshan 0 Aug 27 18:35 mymknod-fifo*
*/
