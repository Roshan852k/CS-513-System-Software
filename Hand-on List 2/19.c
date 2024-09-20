/*  
============================================================================
Name : 19.c
Author : Roshan Yadav
Description : Create a FIFO file by
              a. mknod command
              b. mkfifo command
              c. use strace command to find out, which command (mknod or mkfifo) is better.
              c. mknod system call
              d. mkfifo library function
Date: 15th Sep, 2024.
============================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

void main(){   
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
}

/*
============================================================================
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ mkfifo FIFO
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ strace mkfifo newfifo
execve("/usr/bin/mkfifo", ["mkfifo", "newfifo"], 0x7ffcce1897d8 /* 46 vars */) = 0
brk(NULL)                               = 0x55cee4d97000
arch_prctl(0x3001 /* ARCH_??? */, 0x7fff720633e0) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f05afc61000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=64183, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 64183, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f05afc51000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=174472, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 181928, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f05afc24000
mmap(0x7f05afc2a000, 114688, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x7f05afc2a000
mmap(0x7f05afc46000, 28672, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7f05afc46000
mmap(0x7f05afc4d000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x29000) = 0x7f05afc4d000
mmap(0x7f05afc4f000, 5800, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f05afc4f000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P<\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=2072888, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2117488, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f05afa00000
mmap(0x7f05afa22000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7f05afa22000
mmap(0x7f05afb9a000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7f05afb9a000
mmap(0x7f05afbf2000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1f1000) = 0x7f05afbf2000
mmap(0x7f05afbf8000, 53104, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f05afbf8000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=625344, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 627472, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f05af966000
mmap(0x7f05af968000, 438272, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f05af968000
mmap(0x7f05af9d3000, 176128, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6d000) = 0x7f05af9d3000
mmap(0x7f05af9fe000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x97000) = 0x7f05af9fe000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f05afc21000
arch_prctl(ARCH_SET_FS, 0x7f05afc21800) = 0
set_tid_address(0x7f05afc21ad0)         = 15488
set_robust_list(0x7f05afc21ae0, 24)     = 0
rseq(0x7f05afc22120, 0x20, 0, 0x53053053) = 0
mprotect(0x7f05afbf2000, 16384, PROT_READ) = 0
mprotect(0x7f05af9fe000, 4096, PROT_READ) = 0
mprotect(0x7f05afc4d000, 4096, PROT_READ) = 0
mprotect(0x55cee46c5000, 4096, PROT_READ) = 0
mprotect(0x7f05afc96000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f05afc51000, 64183)           = 0
statfs("/sys/fs/selinux", 0x7fff720633b0) = -1 ENOENT (No such file or directory)
statfs("/selinux", 0x7fff720633b0)      = -1 ENOENT (No such file or directory)
getrandom("\x67\xa8\x25\x35\x59\x60\xaa\x5f", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x55cee4d97000
brk(0x55cee4db8000)                     = 0x55cee4db8000
openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0444, st_size=0, ...}, AT_EMPTY_PATH) = 0
read(3, "nodev\tsysfs\nnodev\ttmpfs\nnodev\tbd"..., 1024) = 407
read(3, "", 1024)                       = 0
close(3)                                = 0
access("/etc/selinux/config", F_OK)     = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=5716304, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 5716304, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f05af200000
close(3)                                = 0
mknodat(AT_FDCWD, "newfifo", S_IFIFO|0666) = 0
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ gcc 19.c -o 19
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-2$ ./19
pipe created successfully using mkfifo
pipe created successfully using mknod
============================================================================
*/


