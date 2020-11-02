#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

struct fds
{
	int epollfd;
	int sockfd;
};

int SetNonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void AddFd(int epollfd, int fd, bool oneshot)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	if(oneshot)
	{
		event.events |= EPOLLONESHOT;
	}
	
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	SetNonblocking(fd);
}

/*重置fd上的事件，这操作以后，尽管fd上的EPOLLONESHOT事件被注册，但是操作系统仍然会触发fd上的EPOLLIN事件，且只触发一次*/
void reset_oneshot(int epollfd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

/*工作线程*/
void* worker(void* arg)
{
	int sockfd = ((struct fds*)arg)->sockfd;
	int epollfd = ((struct fds*)arg)->epollfd;
	printf("start new thread to receive data on fd: %d\n", sockfd);
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	
	while(1)
	{
		int ret = recv(sockfd, buf,BUFFER_SIZE-1, 0);
		if(ret == 0)
		{
			close(sockfd);
			printf("foreigner closed the connection\n");
			break;
		}
		else if(ret < 0)
		{
			if(errno = EAGAIN)
			{
				reset_oneshot(epollfd, sockfd);
				printf("read later\n");
				break;
			}
		}
		else
		{
			printf("get content: %s\n", buf);
			//休眠5秒，模拟数据处理过程
			printf("worker working...\n");
			sleep(5);
		}
	}
	printf("end thread receiving data on fd: %d\n", sockfd);
}

int main(int argc, char* argv[])
{
	if(argc <= 2)
	{
		printf("usage: ip_address + port_number\n");
		return -1;
	}
	
	const char* ip = argv[1];
	int port = atoi(argv[2]);
	
	int ret = -1;
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);
	
	int listenfd = socket(PF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		printf("fail to create socket!\n");
		return -1;
	}
	
	ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
	if(ret == -1)
	{
		printf("fail to bind socket!\n");
		return -1;
	}
	
	ret = listen(listenfd, 5);
	if(ret == -1)
	{
		printf("fail to listen socket\n");
		return -1;
	}
	
	struct epoll_event events[MAX_EVENT_NUMBER];
	int epollfd = epoll_create(5);
	if(epollfd == -1)
	{
		printf("fail to create epoll\n");
		return -1;
	}
	
	//注意，监听socket listenfd上是不能注册EPOLLONESHOT事件的，否则应用程序只能处理一个客户连接！因为后续的客户连接请求将不再触发listenfd的EPOLLIN事件
	AddFd(epollfd, listenfd, false);
	
	
	while(1)
	{
		int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);  //永久等待
		if(ret < 0)
		{
			printf("epoll failure!\n");
			break;
		}
		
		int i;
		for(i = 0; i < ret; i++)
		{
			int sockfd = events[i].data.fd;
			if(sockfd == listenfd)
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
				//对每个非监听文件描述符都注册EPOLLONESHOT事件
				AddFd(epollfd, connfd, true);
			}
			else if(events[i].events & EPOLLIN)
			{
				pthread_t thread;
				struct fds fds_for_new_worker;
				fds_for_new_worker.epollfd = epollfd;
				fds_for_new_worker.sockfd = events[i].data.fd;
				/*新启动一个工作线程为sockfd服务*/
				pthread_create(&thread, NULL, worker, &fds_for_new_worker);
				
			}
			else
			{
				printf("something unexpected happened!\n");
			}
		}
	}
	
	close(listenfd);
	
	return 0;
}