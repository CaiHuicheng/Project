
/* fifo_write.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>		

#define MYFIFO			"/tmp/myfifo"	/* �����ܵ��ļ���*/
#define MAX_BUFFER_SIZE		PIPE_BUF 	/*��������limits.h��*/
	
int main(int argc, char * argv[]) /*����Ϊ����д����ַ���*/
{
	int fd;
	char buff[MAX_BUFFER_SIZE];
	int nwrite;
	
	if(argc <= 1)
	{
		printf("Usage: ./fifo_write string\n");
		exit(1);
	}
	sscanf(argv[1], "%s", buff);
	
	/* ��ֻд������ʽ��FIFO�ܵ� */
	fd = open(MYFIFO, O_WRONLY);
	if (fd == -1)
	{
		printf("Open fifo file error\n");
		exit(1);
	}
	
	/*��ܵ���д���ַ���*/
	if ((nwrite = write(fd, buff, MAX_BUFFER_SIZE)) > 0)
	{
		printf("Write '%s' to FIFO\n", buff);
	}
	
	close(fd);
	exit(0);
}