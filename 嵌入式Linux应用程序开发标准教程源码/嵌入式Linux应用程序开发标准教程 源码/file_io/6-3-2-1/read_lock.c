
/* read_lock.c */

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
	
	fd = open("hello",O_RDWR | O_CREAT, 0644);
	if(fd < 0)
	{
		printf("Open file error\n");
		exit(1);
	}
	
	/* 给文件上读取锁 */
	lock_set(fd, F_RDLCK);
	getchar();
	
	/* 给文件解锁 */
	lock_set(fd, F_UNLCK);
	getchar();
	
	close(fd);
	exit(0);
}