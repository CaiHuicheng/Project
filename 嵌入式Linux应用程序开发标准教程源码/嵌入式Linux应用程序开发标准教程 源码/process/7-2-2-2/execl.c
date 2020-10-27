/* execl.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ret;
	
	if ((ret = fork()) == 0)
	{
		/*����execl������ע������Ҫ����ps�������ڵ�����·��*/
		if ((ret = execl("/bin/ps","ps","-ef",NULL)) < 0)
		{
			printf("Execl error\n");
		}
	}
	
	return ret;
}