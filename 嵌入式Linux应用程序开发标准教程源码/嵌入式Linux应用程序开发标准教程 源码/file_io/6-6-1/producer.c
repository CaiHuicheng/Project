
/* producer.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "mylock.h"

#define MAXLEN			10	/* 缓冲区大小最大值*/

#define ALPHABET		1	/* 表示使用英文字符 */
#define ALPHABET_START		'a'	/* 头一个字符，可以用 'A'*/
#define COUNT_OF_ALPHABET	26	/* 字母字符的个数 */

#define DIGIT			2	/* 表示使用数字字符 */
#define DIGIT_START		'0'	/* 头一个字符 */
#define COUNT_OF_DIGIT		10	/* 数字字符的个数 */

#define SIGN_TYPE	ALPHABET	/* 本实例选用英文字符 */

const char *fifo_file = "./myfifo";	/* 仿真FIFO文件名 */

char buff[MAXLEN];			/* 缓冲区 */

/* 功能：生产一个字符并写入到仿真FIFO文件中 */
int product(void)
{
	int fd;
	unsigned int sign_type, sign_start, sign_count, size;
	static unsigned int counter = 0;
	
	/* 打开仿真FIFO文件 */
	if ((fd = open(fifo_file, O_CREAT|O_RDWR|O_APPEND, 0644)) < 0)
	{
		printf("Open fifo file error\n");
		exit(1);
	}
	
	sign_type =  SIGN_TYPE;

	switch(sign_type)
	{
		case ALPHABET:/* 英文字符 */
		{
			sign_start = ALPHABET_START;
			sign_count = COUNT_OF_ALPHABET;
		}
		break;

		case DIGIT:/* 数字字符 */
		{
			sign_start = DIGIT_START;	
			sign_count = COUNT_OF_DIGIT;
		}
		break;

		default:
		{
			return -1;
		}
	}/*end of switch*/

	sprintf(buff, "%c", (sign_start + counter));
	counter = (counter + 1) % sign_count;
	
	lock_set(fd, F_WRLCK); /* 上写锁*/
	if ((size = write(fd, buff, strlen(buff))) < 0)
	{
		printf("Producer: write error\n");
		return -1;
	}
	lock_set(fd, F_UNLCK); /* 解锁 */

	close(fd);
	return 0;
}

int main(int argc ,char *argv[])
{
	int time_step = 1; /* 生产周期 */
	int time_life = 10; /* 需要生产的资源数 */

	if (argc > 1)
	{
		sscanf(argv[1], "%d", &time_step);
	}
	
	if (argc > 2)
	{
		sscanf(argv[2], "%d", &time_life);
	}
	
	while (time_life--)
	{
		if (product() < 0)
		{
			break;
		}
		sleep(time_step);
	}

	exit(EXIT_SUCCESS);
}