#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//��������б�������NULL��β
	char *envp[]={"PATH=/tmp","USER=david", NULL};
	
	if (fork() == 0)
	{
		//����execle������ע������ҲҪָ��env������·��
		if (execle("/usr/bin/env", "env", NULL, envp) < 0)
		{
			printf("Execle error\n");
		}
	}
}