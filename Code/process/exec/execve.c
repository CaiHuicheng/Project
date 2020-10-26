#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//��������б�������NULL��β
	char *arg[] = {"env", NULL};
	char *envp[] = {"PATH=/tmp", "USER=david", NULL};
	
	if (fork() == 0)
	{
		if (execve("/usr/bin/env", arg, envp) < 0)
		{
			printf("Execve error\n");
		}
	}
}