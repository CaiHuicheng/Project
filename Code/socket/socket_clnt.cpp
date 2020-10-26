#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
	//1、创建socket
	int sock = socket(AF_INET,SOCK_STREAM,0);
	//2、向服务器发起请求
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234);
	connet(sock,(struct sockaddr_in*)&serv_addr,sizeof(serv_addr));
	//3、读取服务器传回信息
	char buffer[1024];
	read(sock,buffer,sizeof(buffer)-1);
	
	printf("Message form server:%s\n",buffer);
	
	//4、关闭连接
	close(sock);
	return 0;
}