/* pid.c */
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main()
{
	/*��õ�ǰ���̵Ľ���ID���丸����ID*/
	printf("The PID of this process is %d\n",getpid());
	printf("The PPID of this process is %d\n",getppid());
	
	return 0;
}
