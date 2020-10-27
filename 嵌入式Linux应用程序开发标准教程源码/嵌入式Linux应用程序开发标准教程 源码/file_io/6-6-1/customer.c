
/* customer.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_FILE_SIZE		100 * 1024 * 1024 /* 100M*/

const char *fifo_file = "./myfifo";		/* 仿真FIFO文件名 */
const char *tmp_file = "./tmp";			/* 临时文件名 */

/* 资源消费函数 */
int customing(const char *myfifo, int need)
{
	int fd;
	char buff;
	int counter = 0;
	
	if ((fd = open(myfifo, O_RDONLY)) < 0)
	{
		printf("Function customing error\n");
		return -1;
	}

	printf("Enjoy:");
	lseek(fd, SEEK_SET, 0);
	 
	while (counter < need)
	{	
		while ((read(fd, &buff, 1) == 1) && (counter < need))
		{
			fputc(buff, stdout); /* 消费就是在屏幕上简单的显示 */
			counter++;
		}
	}
		
	fputs("\n", stdout);
	close(fd);
	return 0;	
}

/* 功能:从sour_file文件的offset偏移处开始将count字节大小的数据拷贝到dest_file文件 */
int myfilecopy(const char *sour_file, const char *dest_file, int offset, int count, int copy_mode)
{
	int in_file, out_file;
	int counter = 0;
	char buff_unit;

	if ((in_file = open(sour_file, O_RDONLY|O_NONBLOCK)) < 0)
	{
		printf("Function myfilecopy error in source file\n");
		return -1;
	}
	
	if ((out_file = open(dest_file, O_CREAT|O_RDWR|O_TRUNC|O_NONBLOCK, 0644)) < 0)
	{
		printf("Function myfilecopy error in destination file:");
		return -1;
	}

	lseek(in_file, offset, SEEK_SET);
	while ((read(in_file, &buff_unit, 1) == 1) && (counter < count))
	{
		write(out_file, &buff_unit, 1);
		counter++;
	}
	
	close(in_file);
	close(out_file);

	return 0;
}

/* 功能：实现FIFO消费者 */
int custom(int need)
{
	int fd;

	/* 对资源进行消费，need表示该消费的资源数目 */
	customing(fifo_file, need);
	
	if ((fd = open(fifo_file, O_RDWR)) < 0)
	{
		printf("Function myfilecopy error in source_file:");
		return -1;
	}

	/* 为了模拟FIFO结构，对整个文件内容进行平行移动 */
	lock_set(fd, F_WRLCK);
 	myfilecopy(fifo_file, tmp_file, need, MAX_FILE_SIZE, 0);
	myfilecopy(tmp_file, fifo_file, 0, MAX_FILE_SIZE, 0);
	lock_set(fd, F_UNLCK);
	
	unlink(tmp_file);	
	close(fd);
	return 0;
}

int main(int argc ,char *argv[])
{
	int customer_capacity = 10;
	
	if (argc > 1) /* 第一个参数指定需要消费的资源数目，默认值为10 */
	{
		sscanf(argv[1], "%d", &customer_capacity);
	}
	
	if (customer_capacity > 0)
	{
		custom(customer_capacity);
	}

	exit(EXIT_SUCCESS);
}