/*  
	Name - Roshan Yadav
	Roll No - MT2024169
	Problem - Write a simple program to execute in an infinite loop at the background. Go to /proc directory and identify all the process related information in the corresponding proc directory.
*/

#include<stdio.h>

int main(){
	int i =5;
	while(i){
	}
	return 0;
}

/*
oshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ gcc 2.c -o 2
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./2 
^C  
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ ./2 &
[1] 8350
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:~/Software_System/hand-on-1$ cd /proc
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:/proc$ cd 8350
roshan@roshan-ASUS-TUF-Gaming-F15-FX506HF-FX506HF:/proc/8350$ cat status
Name:	2
Umask:	0002
State:	R (running)
Tgid:	8350
Ngid:	0
Pid:	8350
PPid:	4628
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	4 24 27 30 46 100 118 1000 
NStgid:	8350
NSpid:	8350
NSpgid:	8350
NSsid:	4628
VmPeak:	    2548 kB
VmSize:	    2484 kB
VmLck:	       0 kB
VmPin:	       0 kB
VmHWM:	     896 kB
VmRSS:	     896 kB
RssAnon:	       0 kB
RssFile:	     896 kB
RssShmem:	       0 kB
VmData:	      92 kB
VmStk:	     132 kB
VmExe:	       4 kB
VmLib:	    1672 kB
VmPTE:	      40 kB
VmSwap:	       0 kB
HugetlbPages:	       0 kB
CoreDumping:	0
THP_enabled:	1
Threads:	1
SigQ:	0/30388
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000000
SigCgt:	0000000000000000
CapInh:	0000000000000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	000001ffffffffff
CapAmb:	0000000000000000
NoNewPrivs:	0
Seccomp:	0
Seccomp_filters:	0
Speculation_Store_Bypass:	thread vulnerable
SpeculationIndirectBranch:	conditional enabled
Cpus_allowed:	fff
Cpus_allowed_list:	0-11
Mems_allowed:	00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	0
nonvoluntary_ctxt_switches:	68
*/
