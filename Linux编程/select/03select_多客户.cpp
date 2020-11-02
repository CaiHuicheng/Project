#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <sys/time.h> 
#include <sys/ioctl.h> 
#include <unistd.h> 
#include <stdlib.h>

int main() 
{ 
    int server_sockfd, client_sockfd; 
    int server_len, client_len; 
    struct sockaddr_in server_address; 
    struct sockaddr_in client_address; 
    int result; 
    fd_set readfds, testfds; 
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);//建立服务器端socket 
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_address.sin_port = htons(8888); 
    server_len = sizeof(server_address); 
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len); 
    listen(server_sockfd, 5); //监听队列最多容纳5个 
    FD_ZERO(&readfds); 
    FD_SET(server_sockfd, &readfds);//将服务器端socket加入到集合中
    while(1) 
    {
        char ch; 
        int fd; 
        int nread; 
        testfds = readfds;//将需要监视的描述符集copy到select查询队列中，select会对其修改，所以一定要分开使用变量 
        printf("server waiting\n"); 

        /*无限期阻塞，并测试文件描述符变动 */
        result = select(FD_SETSIZE, &testfds, (fd_set *)0,(fd_set *)0, (struct timeval *) 0); //FD_SETSIZE：系统默认的最大文件描述符
        if(result < 1) 
        { 
            perror("server5"); 
            exit(1); 
        } 

        /*扫描所有的文件描述符*/
        for(fd = 0; fd < FD_SETSIZE; fd++) 
        {
            /*找到相关文件描述符*/
            if(FD_ISSET(fd,&testfds)) 
            { 
              /*判断是否为服务器套接字，是则表示为客户请求连接。*/
                if(fd == server_sockfd) 
                { 
                    client_len = sizeof(client_address); 
                    client_sockfd = accept(server_sockfd, 
                    (struct sockaddr *)&client_address, &client_len); 
                    FD_SET(client_sockfd, &readfds);//将客户端socket加入到集合中
                    printf("adding client on fd %d\n", client_sockfd); 
                } 
                /*客户端socket中有数据请求时*/
                else 
                { 
                    ioctl(fd, FIONREAD, &nread);//取得数据量交给nread
                    
                    /*客户数据请求完毕，关闭套接字，从集合中清除相应描述符 */
                    if(nread == 0) 
                    { 
                        close(fd); 
                        FD_CLR(fd, &readfds); //去掉关闭的fd
                        printf("removing client on fd %d\n", fd); 
                    } 
                    /*处理客户数据请求*/
                    else 
                    { 
                        read(fd, &ch, 1); 
                        sleep(5); 
                        printf("serving client on fd %d\n", fd); 
                        ch++; 
                        write(fd, &ch, 1); 
                    } 
                } 
            } 
        } 
    } 

    return 0;