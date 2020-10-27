
/* net_fcntl.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>

#define PORT				1234
#define MAX_QUE_CONN_NM		5
#define BUFFER_SIZE			1024

int main()
{
	struct sockaddr_in server_sockaddr, client_sockaddr;
	int sin_size, recvbytes, flags;
	int sockfd, client_fd;
	char buf[BUFFER_SIZE];
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	
	server_sockaddr.sin_family=AF_INET;
	server_sockaddr.sin_port=htons(PORT);
	server_sockaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);
	
	int i = 1;/* 使得重复使用本地地址与套接字进行绑定 */
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
	
	if (bind(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	
	if(listen(sockfd,MAX_QUE_CONN_NM)== -1)
	{
		perror("listen");
		exit(1);
	}
	printf("Listening....\n");
	
	/* 调用fcntl函数设置非阻塞属性 */
	flags = fcntl(sockfd, F_GETFL);
	if (flags < 0 || fcntl(sockfd, F_SETFL, flags|O_NONBLOCK) < 0)
	{
		perror("fcntl");
		exit(1);
	}
		
 	while(1)
 	{
 		sin_size = sizeof(struct sockaddr_in);
 		if ((client_fd = accept(sockfd, (struct sockaddr*)&client_sockaddr, &sin_size)) < 0)
 		{
 			perror("accept");
 			exit(1);
 		}
 		
 		if ((recvbytes = recv(client_fd, buf, BUFFER_SIZE, 0)) < 0)
 		{
 			perror("recv");
 			exit(1);
 		}
 		
 		printf("Received a message: %s\n", buf);
  } /*while*/
  
  close(client_fd);
  exit(1);
}