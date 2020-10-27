
/* kill_raise.c */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int ret;
	
	/* 创建一子进程 */
	if ((pid = fork()) < 0)
	{
		printf("Fork error\n");
		exit(1);
	}
	
	if (pid == 0)
	{
		/* 在子进程中使用raise函数发出SIGSTOP信号,使子进程暂停 */
		printf("Child(pid : %d) is waiting for any signal\n", getpid());
		raise(SIGSTOP);
		exit(0);
	}
	else
	{
		/* 在父进程中收集子进程发出的信号，并调用kill函数进行相应的操作 */
		if ((waitpid(pid, NULL, WNOHANG)) == 0)
		{
			if ((ret = kill(pid, SIGKILL)) == 0)
			{
				printf("Parent kill %d\n",pid);
			}
			else
			{
				printf("Parent kill error\n");
			}
		}
		
		waitpid(pid, NULL, 0);
		exit(0);
	}

}