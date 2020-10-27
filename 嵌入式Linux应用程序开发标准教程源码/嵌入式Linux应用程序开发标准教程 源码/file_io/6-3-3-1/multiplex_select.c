
/* multiplex_select.c */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define MAX_BUFFER_SIZE		1024			/* ��������С*/
#define IN_FILES		3			/* ��·���������ļ���Ŀ*/
#define TIME_DELAY		60			/* ��ʱʱ������ */
#define MAX(a, b)		((a > b)?(a):(b))

int main(void)
{
	int fds[IN_FILES];
	char buf[MAX_BUFFER_SIZE];
	int i, res, real_read, maxfd;
	struct timeval tv;
	fd_set inset,tmp_inset;
	
	/*���Ȱ�һ����Ȩ�޴�����Դ�ļ�*/
	fds[0] = 0;
	
	if((fds[1] = open ("in1", O_RDONLY|O_NONBLOCK)) < 0)
	{
		printf("Open in1 error\n");
		return 1;
	}
  		    
 	if((fds[2] = open ("in2", O_RDONLY|O_NONBLOCK)) < 0)
 	{
 		printf("Open in2 error\n");
		return 1;
	}

	/*ȡ�������ļ��������еĽϴ���*/
  	maxfd = MAX(MAX(fds[0], fds[1]), fds[2]);
  	

  	/*��ʼ��������inset�����ڶ������м�����Ӧ��������*/
  	FD_ZERO(&inset); 
  	for (i = 0; i < IN_FILES; i++)
  	{
  		FD_SET(fds[i], &inset);
  	}
  	FD_SET(0, &inset);

  	tv.tv_sec = TIME_DELAY;
  	tv.tv_usec = 0;
  	
  	/*ѭ�����Ը��ļ��������Ƿ�׼��������������select����������ļ�����������Ӧ����*/
  	while(FD_ISSET(fds[0],&inset) || FD_ISSET(fds[1],&inset) || FD_ISSET(fds[2], &inset))
  	{ 
  		tmp_inset = inset;
  		res = select(maxfd + 1, &tmp_inset, NULL, NULL, &tv);
  		
  		switch(res)
  		{
  			case -1:
  			{
  				printf("Select error\n");
  				return 1;
  			}
  			break;
  			
  			case 0: /* Timeout */
  			{
  				printf("Time out\n");
  				return 1;
  			}  			
  			break;
  			
  			default:
  			{
  				for (i = 0; i < IN_FILES; i++)
  				{
  					if (FD_ISSET(fds[i], &tmp_inset))
		  			{
		  				memset(buf, 0, MAX_BUFFER_SIZE);
		  				real_read = read(fds[i], buf, MAX_BUFFER_SIZE);
		  		
		  				if (real_read < 0)
		  				{
		  					if (errno != EAGAIN)
		  					{
		  						return 1;
		  					}
		  				}
		  				else if (!real_read)
		  				{
		  					close(fds[i]);
		  					FD_CLR(fds[i], &inset);
		  				}
		  				else
		  				{
		  					if (i == 0)
		  					{
		  						if ((buf[0] == 'q') || (buf[0] == 'Q'))
		  						{
		  							return 1;
		  						}
		  					}
		  					else
		  					{
		  						buf[real_read] = '\0';
		  						printf("%s", buf);
		  					}
		  				}
		  			} /* end of if */  					
  				} /* end of for */
  			}
  			break;  		
  			
  		} /* end of switch */ 		
  	} /*end of while */
  	
  	exit(0);
}