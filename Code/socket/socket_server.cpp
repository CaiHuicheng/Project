#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	//1、重建socket(协议族，数据流，传输协议)
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2、socket IP和端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//IP地址
	serv_addr.sin_port = htons(1234);//端口
	bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	//3、监听
	listen(serv_sock,20);
	//4、接收客户端请求
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	//5、向客户端发送数据
	char str[] = "test World";
	write(clnt_sock,str,sizeof(str));
	//6、关闭连接
	close(clnt_sock);
	close(serv_sock);
}