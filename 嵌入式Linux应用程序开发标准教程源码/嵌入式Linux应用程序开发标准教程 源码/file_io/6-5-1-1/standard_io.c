
/* standard_io.c */

#include <stdlib.h>
#include <stdio.h>

#define	BUFFER_SIZE	1024		/* 每次读写缓存大小 */
#define SRC_FILE_NAME	"src_file"	/* 源文件名 */
#define DEST_FILE_NAME	"dest_file"	/* 目标文件名文件名 */
#define OFFSET		10240		/* 拷贝的数据大小 */
 	
int main()
{
	FILE *src_file, *dest_file;
	unsigned char buff[BUFFER_SIZE];
	int real_read_len;
	
	/* 以只读方式打开源文件 */
	src_file = fopen(SRC_FILE_NAME, "r");
	
	/* 以只写方式打开目标文件，若此文件不存在则创建 */
	dest_file = fopen(DEST_FILE_NAME, "w");
	
	if (!src_file || !dest_file)
	{
		printf("Open file error\n");
		exit(1);
	}
	
	/* 将源文件的读写指针移到最后10KB的起始位置*/
	fseek(src_file, -OFFSET, SEEK_END);
	
	/* 读取源文件的最后10KB数据并写到目标文件中，每次读写1KB */
	while ((real_read_len = fread(buff, 1, sizeof(buff), src_file)) > 0)
	{
		fwrite(buff, 1, real_read_len, dest_file);
	}
	
	fclose(dest_file);
	fclose(src_file);
	return 0;	
}