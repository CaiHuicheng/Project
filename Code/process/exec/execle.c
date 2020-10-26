#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//命令参数列表，必须以NULL结尾
	char *envp[]={"PATH=/tmp","USER=david", NULL};
	
	if (fork() == 0)
	{
		//调用execle函数，注意这里也要指出env的完整路径
		if (execle("/usr/bin/env", "env", NULL, envp) < 0)
		{
			printf("Execle error\n");
		}
	}
}