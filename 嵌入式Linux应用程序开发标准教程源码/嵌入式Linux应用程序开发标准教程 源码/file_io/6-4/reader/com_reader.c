/* com_reader.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "uart_api.h"

int main(void) 
{
	int fd;
	char buff[BUFFER_SIZE];
	
	if((fd = open_port(TARGET_COM_PORT)) < 0) /* ´ò¿ª´®¿Ú */
	{
		perror("open_port");
		return 1;
	}
	
	if(set_com_config(fd, 115200, 8, 'N', 1) < 0) /* ÉèÖÃ´®¿Ú */
	{
		perror("set_com_config");
		return 1;
	}
	
	do
	{
		memset(buff, 0, BUFFER_SIZE);
		if (read(fd, buff, BUFFER_SIZE) > 0)
		{
			printf("The received words are : %s", buff);
		}
	} while(strncmp(buff, "quit", 4));

  	close(fd);
  	return 0;
}
