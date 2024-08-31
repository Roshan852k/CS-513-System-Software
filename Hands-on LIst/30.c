/* 
============================================================================
Name : 29.c
Author : Roshan Yadav
Description : Write a program to run a script at a specific time using a Daemon process. 
Date: 30th Aug, 2024.
============================================================================
*/

#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

void Daemon(){
    int pId;
    pId = fork();
    if (pId < 0) {
        exit(1);
    }
    if (pId > 0) {
        exit(0);
    }
    
    umask(0);
 
    if (setsid() < 0) {
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(1);
    }

    // Parse target time
    int target_hour = atoi(argv[1]);
    int target_minute = atoi(argv[2]);
    int target_second = (argc > 3) ? atoi(argv[3]) : 0;
    char *sc = argv[4];

    time_t curr_epoch, deadline_epoch;
    struct tm *deadline_tm;

    time(&curr_epoch);
    deadline_tm = localtime(&curr_epoch);

    deadline_tm->tm_sec = target_second;
    deadline_tm->tm_hour = target_hour;
    deadline_tm->tm_min = target_minute;

    deadline_epoch = mktime(deadline_tm);

    if (deadline_epoch == -1) {
        perror("Error converting deadline to epoch\n");
        exit(1);
    }
    Daemon();
    while (1) {
        time(&curr_epoch);
        if (difftime(deadline_epoch, curr_epoch) <= 0) {
            printf("Running the given script %s\n",sc);
            execl(sc, sc, (char *)NULL); // Run the script
            exit(0);  // Exit after running the script
        }
        sleep(1); // Check every 1 seconds
    }

    exit(0);
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 30.c -o 30
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./30 18 56 00 /bin/ls
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ Running the given script /bin/ls
 10.c	   18b	   27c.c      cp_hello.txt     record.c
 11a.c	   18b.c   27d.c      fifo	       record.txt
 11b.c	   19.c    27e.c      filewrite.txt    sample_1.txt
 11c.c	   1a.c    28.c       hardlink	       sample_2.txt
 12.c	   1b.c    29.c       hardlink1        sample_3.txt
 13.c	   1c.c    2.c	      hello.txt        sample_4.txt
 14.c	   1.sh    30	      link	       sample_5.txt
 15.c	   20.c    30.c       my_file.txt      softlink
 16a.c	   21.c    30_old.c   mymkfifo	       softlink1
 16b.c	   22.c    3.c	      mymknod-fifo     test
 17	   23.c    4.c	      my-repo	      'test (copy).txt'
 17a	   24.c    5.c	     ' new_file.txt'   testing.c
 17.c	   25.c    6.c	      pass_key	       test.txt
 17_db.c   26.c    7.c	      pass_key.pub     ticket_db
 18a	   27a.c   8.c	      read.txt	       ticketfile.txt
 18a.c	   27b.c   9.c	      record	       ticket_record.txt
============================================================================
*/
