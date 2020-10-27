/* write_lock.c */
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "lock_set.c"

int main(void)
{
	int fd;
	
	/* ���ȴ��ļ� */
	fd = open("hello",O_RDWR | O_CREAT, 0644);
	if(fd < 0)
	{
		printf("Open file error\n");
		exit(1);
	}
	
	/* ���ļ���д���� */
	lock_set(fd, F_WRLCK);
	getchar();
	
	/* ���ļ����� */
	lock_set(fd, F_UNLCK);
	getchar();
	
	close(fd);
	
	exit(0);
}