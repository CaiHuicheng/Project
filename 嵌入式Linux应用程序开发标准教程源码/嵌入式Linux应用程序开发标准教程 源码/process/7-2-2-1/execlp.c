/*execlp.c*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ret;
	
	if ((ret = fork()) == 0)
	{
		/*����execlp�����������൱�ڵ�����"ps -ef"����*/
		if ((ret = execlp("ps", "ps", "-ef", NULL)) < 0)
		{
			printf("Execlp error\n");
		}
	}
	
	return ret;
}
