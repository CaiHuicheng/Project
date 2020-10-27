
/* standard_io.c */

#include <stdlib.h>
#include <stdio.h>

#define	BUFFER_SIZE	1024		/* ÿ�ζ�д�����С */
#define SRC_FILE_NAME	"src_file"	/* Դ�ļ��� */
#define DEST_FILE_NAME	"dest_file"	/* Ŀ���ļ����ļ��� */
#define OFFSET		10240		/* ���������ݴ�С */
 	
int main()
{
	FILE *src_file, *dest_file;
	unsigned char buff[BUFFER_SIZE];
	int real_read_len;
	
	/* ��ֻ����ʽ��Դ�ļ� */
	src_file = fopen(SRC_FILE_NAME, "r");
	
	/* ��ֻд��ʽ��Ŀ���ļ��������ļ��������򴴽� */
	dest_file = fopen(DEST_FILE_NAME, "w");
	
	if (!src_file || !dest_file)
	{
		printf("Open file error\n");
		exit(1);
	}
	
	/* ��Դ�ļ��Ķ�дָ���Ƶ����10KB����ʼλ��*/
	fseek(src_file, -OFFSET, SEEK_END);
	
	/* ��ȡԴ�ļ������10KB���ݲ�д��Ŀ���ļ��У�ÿ�ζ�д1KB */
	while ((real_read_len = fread(buff, 1, sizeof(buff), src_file)) > 0)
	{
		fwrite(buff, 1, real_read_len, dest_file);
	}
	
	fclose(dest_file);
	fclose(src_file);
	return 0;	
}