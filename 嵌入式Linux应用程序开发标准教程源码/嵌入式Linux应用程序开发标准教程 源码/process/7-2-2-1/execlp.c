/*execlp.c*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ret;
	
	if ((ret = fork()) == 0)
	{
		/*调用execlp函数，这里相当于调用了"ps -ef"命令*/
		if ((ret = execlp("ps", "ps", "-ef", NULL)) < 0)
		{
			printf("Execlp error\n");
		}
	}
	
	return ret;
}
