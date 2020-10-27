/* execl.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ret;
	
	if ((ret = fork()) == 0)
	{
		/*调用execl函数，注意这里要给出ps程序所在的完整路径*/
		if ((ret = execl("/bin/ps","ps","-ef",NULL)) < 0)
		{
			printf("Execl error\n");
		}
	}
	
	return ret;
}