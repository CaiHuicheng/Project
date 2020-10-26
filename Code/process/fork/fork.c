/* fork.c */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t result;
	
	//调用fork函数，其返回值为result
	result = fork();
	
	//通过result的值来判断fork函数的返回情况，首先进行出错处理
	if(result ==  -1)
	{
		printf("Fork error\n");
	}
	else if (result == 0) //子进程
	{
		printf("The return value is %d\nIn child process!!\nMy PID is %d\n",result,getpid());
	}
	else //父进程
	{
		printf("The return value is %d\nIn father process!!\nMy PID is %d\n",result,getpid());
	}
	
	return result;
}
