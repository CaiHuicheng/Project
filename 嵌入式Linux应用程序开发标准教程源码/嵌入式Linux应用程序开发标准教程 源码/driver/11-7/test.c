
/* test.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define 	TEST_DEVICE_FILENAME		"/dev/test_dev"
#define		BUFF_SZ				1024

int main()
{
	int fd, nwrite, nread;
	char buff[BUFF_SZ];

	fd = open(TEST_DEVICE_FILENAME, O_RDWR);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
		
	do
	{
		printf("Input some words to kernel(enter 'quit' to exit):");
		memset(buff, 0, BUFF_SZ);
		if (fgets(buff, BUFF_SZ, stdin) == NULL)
		{
			perror("fgets");
			break;
		}
		buff[strlen(buff) - 1] = '\0';
		
		if (write(fd, buff, strlen(buff)) < 0)
		{
			perror("write");
			break;
		}
		
		if (read(fd, buff, BUFF_SZ) < 0)
		{
			perror("read");
			break;
		}
		else
		{
			printf("The read string is from kernel:%s\n", buff);
		}
		
	} while(strncmp(buff, "quit", 4));
	
	close(fd);
	exit(0);
}