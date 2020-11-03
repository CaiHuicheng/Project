
#include <stdio.h>
#include "amqpclient.h"
 
int main()
{
    const char* hostname = "192.168.12.20";
    const int   port = 5672;
    const char* user = "woniu201";
    const char* pwd  = "woniu201";
    const char* vhost = "/";
    const char* queuename = "queuename001";
 
    AmqpClient amqpClient(hostname, port, user, pwd, vhost, queuename);
    amqpClient.ConnectRabbitmq();
    printf("connect rabbitmq succ, is consuming!\n");
    amqpClient.StartConsumer();
 
    return 1;
}
