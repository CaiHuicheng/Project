
/* standard_pipe.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main()
{
	FILE *fp;
	char *cmd = "ps -ef";
	char buf[BUFSIZE];
	
	/*调用popen函数执行相应的命令*/
	if ((fp = popen(cmd, "r")) == NULL)
	{
		printf("Popen error\n");
		exit(1);
	}
	
	while ((fgets(buf, BUFSIZE, fp)) != NULL)
	{
		printf("%s",buf);
	}
	
	pclose(fp);
	exit(0);
}