#include <iostream>
#include <string>
#include <vector>
#include "MessageQueue/RabbitMQ.h"
#include "MessageQueue/MessageBody.h"
#include <ctime>
#include <set>
//#include <vld.h>
using namespace std;
#include <Windows.h>
 
//--------------------------需要开发者自己填写的信息begin--------------------------------------
//服务端的一个Exchange，客户端发送的时候，如果没有则会创建；客户端取的时候，如果没有则取不到数据
CExchange my_test_exchange("MyTestExchange");
//服务端的一个消息队列，客户端发送的时候，如果没有则会创建；客户端取的时候，如果没有则取不到数据
CQueue my_test_queue("MyTestQueue");
//服务端Exchange与消息队列之间的绑定key，客户端发送的时候，如果没有则不能发送；客户端取的时候，如果没有则取不到数据
string my_test_bind_key("MyTestBindKey");
//RabbitMQ服务端IP
string rabbitmq_server_ip = "localhost";
//RabbitMQ服务端端口
int rabbitmq_server_port = 5672;
//RabbitMQ服务端登录用户名
string rabbitmq_server_user = "guest";
//RabbitMQ服务端登录密码
string rabbitmq_server_psw = "guest";
//--------------------------需要开发者自己填写的信息end--------------------------------------
 
 
//--------------------------建议开发者设置批量操作begin--------------------------------------
//建议将此值设置成500，或者1000.这样可以节省时间和网络资源。没有必要一条一条的发送或者取
int test_send_number = 100;
int test_get_number = 200;
//--------------------------建议开发者设置批量操作end--------------------------------------
//引用全局变量
std::multiset<int> MySet;
//发送数据到RabbitMQ服务的全部过程如下:
//！！！每次publish之前必须调用Connect，publish之后调用Disconnect！！！
DWORD WINAPI  send_message_to_mq(LPVOID lpParameter)
{
	vector<CMessage> message_array;
	CMessage message("");
	//制作test_send_number个消息，用于发送到RabbitMQ服务器
	for (int i=0;i<test_send_number;++i)
	{
		//这里创建你要发送的数据，放到CMessage的m_data成员变量中，从服务端取的时候也是一样从这个成员中取string
		message.m_data = std::to_string((long long)i);
		message_array.push_back(message);
	}
	string& err = GetErr();    
	//RabbitMQ服务器的连接信息，这里改成你自己的IP/PORT
	CRabbitMQ pro(rabbitmq_server_ip,rabbitmq_server_port,rabbitmq_server_user,rabbitmq_server_psw);
 
	if(pro.Connect(err)<0)
	{
		cout<<"连接失败！"<<endl;
		return -1;
	}
	else
	{
		cout<<"连接成功！"<<endl;
	}
 
	//声明一个交换机，声明一次，下次不需要再次声明
	if(pro.exchange_declare(my_test_exchange, err) < 0)
	{
		cout<<"声明交换机失败！"<<endl;
		return -1;
	}
	else
	{
		cout<<"声明交换机成功！"<<endl;
	}
	//声明一个队列，声明一次，下次不需要再次声明
	if( (pro.queue_declare(my_test_queue, err) < 0) ) 
	{
		cout<<"声明队列失败！"<<endl;
		return -1;
	}
	else
	{
		cout<<"声明队列成功！"<<endl;
	}
	//将交换机绑定到队列， 绑定一次，后面不需要再绑定
	if( (pro.queue_bind(my_test_queue,my_test_exchange,my_test_bind_key, err)<0) ) 
	{
		cout<<"绑定队列失败！"<<endl;
		return -1;
	}
	else
	{
		cout<<"绑定队列成功！"<<endl;
	}
	string my_test_root_key=my_test_bind_key;
	//发送数据到RabbitMQ服务器，可以反复调用从而实现连续发送数据
	int flag = pro.publish(message_array,my_test_root_key,err);
 
	if(flag<0)
	{
		cout<<"投递消息到MQ失败"<<endl;
	}
	else
	{
		cout<<"投递消息到MQ成功:"<<endl;
		for (vector<CMessage>::iterator itr = message_array.begin(); itr != message_array.end(); ++itr)
		{
			cout<<(*itr).m_data<<" ";
		}
		cout<<endl;
	}
	pro.__sleep(10);
	pro.Disconnect();
 
	return 0;
}
//从RabbitMQ取数据的全部过程如下
//！！！每次consumer之前必须调用Connect，publish之后调用Disconnect！！！
DWORD WINAPI   get_message_from_mq(LPVOID lpParameter)
{
	vector<CMessage> message_array;
	string& err = GetErr();    
 
	//RabbitMQ服务器的连接信息，这里改成你自己的IP/PORT
	CRabbitMQ pro(rabbitmq_server_ip,rabbitmq_server_port,rabbitmq_server_user,rabbitmq_server_psw);
	pro.__sleep(1000);//等待生产者发送完毕再取
	if(pro.Connect(err)<0)
	{
		cout<<"取消息时连接失败！"<<endl;
		return -1;
	}
	else
	{
		cout<<"取消息时连接成功！"<<endl;
	}
	message_array.clear();
	//一次性取1000個消息，不足1000也无妨，有多少取到多少
	int get_number= test_get_number;
	::timeval tvb={0,10};
	//从RabbitMQ服务器取消息
	if(pro.consumer(my_test_queue,message_array,get_number,&tvb,err)<0)
	{
		cout<<"取消息失败！"<<endl;
	}
	else
	{
		cout<<"取消息成功！取到了"<<message_array.size()<<"个消息:"<<endl;
		for (int i=0;i<message_array.size();i++)
		{
			cout<<message_array[i].m_data<<" ";
			MySet.insert(std::stoi(message_array[i].m_data));
		}
		cout<<endl;
	}
	pro.__sleep(10);
	pro.Disconnect();
}
DWORD WINAPI   test_assert_success(LPVOID lpParameter)
{
	CRabbitMQ pro;
	pro.__sleep(2000);
	cout<<"全部数据（验证是否丢失）："<<endl;
	for (auto itr = MySet.begin(); itr != MySet.end(); ++itr)
	{
		cout<<*itr<<" ";
	}
	cout<<endl;
	return 0;
}
int main(int ,char**)
{
	cout<<"Hello UseMQ!"<<endl;
 
	//创建线程  
	HANDLE t1 = CreateThread(NULL, 0, send_message_to_mq, 0, 0, NULL);  
	HANDLE t2 = CreateThread(NULL, 0, send_message_to_mq, 0, 0, NULL); 
 
	HANDLE t3 = CreateThread(NULL, 0, get_message_from_mq, 0, 0, NULL); 
 
	HANDLE t4 = CreateThread(NULL, 0, test_assert_success, 0, 0, NULL); 
	//发送消息
	//send_message_to_mq();
	//取消息
	//get_message_from_mq();
 
	//等待线程退出  
	WaitForSingleObject(t1, INFINITE);  
	WaitForSingleObject(t2, INFINITE);  
	WaitForSingleObject(t3, INFINITE);  
	WaitForSingleObject(t4, INFINITE);  
 
	cout<<"Hello UseMQ end!";
	return 0;
};