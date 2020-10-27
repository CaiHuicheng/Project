/* pid.c */
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main()
{
	/*获得当前进程的进程ID和其父进程ID*/
	printf("The PID of this process is %d\n",getpid());
	printf("The PPID of this process is %d\n",getppid());
	
	return 0;
}
