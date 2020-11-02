//客户端
/*
运行流程：

客户端：启动->连接服务器->发送A->等待服务器回复->收到B->再发B给服务器->收到C->结束

服务器：启动->select->收到A->发A+1回去->收到B->发B+1过去
*/
#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/time.h>

int main() 
{ 
    int client_sockfd; 
    int len; 
    struct sockaddr_in address;//服务器端网络地址结构体 
     int result; 
    char ch = 'A'; 
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);//建立客户端socket 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(8888); 
    len = sizeof(address); 
    result = connect(client_sockfd, (struct sockaddr *)&address, len); 
    if(result == -1) 
    { 
         perror("oops: client2"); 
         exit(1); 
    } 
    //第一次读写
    write(client_sockfd, &ch, 1); 
    read(client_sockfd, &ch, 1); 
    printf("the first time: char from server = %c\n", ch); 
    sleep(5);
    
    //第二次读写
    write(client_sockfd, &ch, 1); 
    read(client_sockfd, &ch, 1); 
    printf("the second time: char from server = %c\n", ch);
    
    close(client_sockfd); 
   
    return 0; 
}
