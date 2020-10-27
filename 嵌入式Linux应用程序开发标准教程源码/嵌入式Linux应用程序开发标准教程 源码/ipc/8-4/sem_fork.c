
/* fork.c */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define DELAY_TIME		3

int main(void)
{
	pid_t result;
	int sem_id;

	sem_id = semget(ftok(".", 'a'),  1, 0666|IPC_CREAT); /* 创建一个信号量*/
	init_sem(sem_id, 0);

	/*调用fork函数，其返回值为result*/
	result = fork();
	
	/*通过result的值来判断fork函数的返回情况，首先进行出错处理*/
	if(result ==  -1)
	{
		perror("Fork\n");
	}
	else if (result == 0) /*返回值为0代表子进程*/
	{
		printf("Child process will wait for some seconds...\n");
		sleep(DELAY_TIME);
		printf("The returned value is %d in the child process(PID = %d)\n", result, getpid());
		sem_v(sem_id);
	}
	else /*返回值大于0代表父进程*/
	{
		sem_p(sem_id);
		printf("The returned value is %d in the father process(PID = %d)\n", result, getpid());
		sem_v(sem_id);
		del_sem(sem_id);
	}
	
	exit(0);
}