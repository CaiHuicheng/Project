//客户端
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
    char str1[] = "ABCDE"; 
    char str2[] = "ABCDEFGHIJK"; 
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
    write(client_sockfd, str1, sizeof(str1)); 

    sleep(5);
    
    //第二次读写
    write(client_sockfd, str2, sizeof(str2)); 

    
    close(client_sockfd); 
   
    return 0; 
}