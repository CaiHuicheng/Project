
/* pipe.c */

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LEN	256
#define DELAY_TIME	1

int main()
{
	pid_t pid;
	int pipe_fd[2];
	char buf[MAX_DATA_LEN];
	const char data[] = "Pipe Test Program";
	int real_read, real_write;
	
	memset((void*)buf, 0, sizeof(buf));
	
	/* �����ܵ� */
	if (pipe(pipe_fd) < 0)
	{
		printf("pipe create error\n");
		exit(1);
	}
	
	/* ����һ�ӽ��� */
	if ((pid = fork()) == 0)
	{
		/* �ӽ��̹ر�д����������ͨ��ʹ�ӽ�����ͣ1��ȴ��������ѹر���Ӧ�Ķ������� */
		close(pipe_fd[1]);
		sleep(DELAY_TIME * 3);
		
		/* �ӽ��̶�ȡ�ܵ����� */
		if ((real_read = read(pipe_fd[0], buf, MAX_DATA_LEN)) > 0)
		{
			printf("%d bytes read from the pipe is '%s'\n", real_read, buf);
		}
		
		/* �ر��ӽ��̶������� */
		close(pipe_fd[0]);
		exit(0);
	}
	else if (pid > 0)
	{
		/* �����̹رն�����������ͨ��ʹ��������ͣ1��ȴ��ӽ����ѹر���Ӧ��д������ */
		close(pipe_fd[0]);
		sleep(DELAY_TIME);
		
		/* ��������ܵ���д���ַ��� */
		if((real_write = write(pipe_fd[1], data, strlen((const char*)data))) !=  -1)
		{
			printf("Parent wrote %d bytes : '%s'\n", real_write, data);
		}
		
		
		/*�رո�����д������*/
		close(pipe_fd[1]);
		
		/*�ռ��ӽ����˳���Ϣ*/
		waitpid(pid, NULL, 0);
		exit(0);
	}
}