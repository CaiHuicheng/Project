#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <iostream>

#include "RabbitmqClient.h"
#include <thread>

using namespace std;

std::string vecRecvMsg;

extern bool bhave;
void RecvData(CRabbitmqClient* client)
{
    std::string strQueuename = "4.3keti";

    
    int iRet = client->Consumer(strQueuename, vecRecvMsg, 1);
    printf("Rabbitmq Consumer Ret: %d\n", iRet);

    

    client->Disconnect();
}

void CoutData()
{
    while (1)
    {
        if (bhave == true)
        {
            
                printf("Consumer: %s\n", vecRecvMsg.c_str());
            

            bhave = false;
        }
        
    }
}

int main()
{
    CRabbitmqClient objRabbitmq;

    std::string strIP = "192.168.10.203";
    int iPort = 5672;
    std::string strUser = "rabbitadmin";
    std::string strPasswd = "123456";


    int iRet = objRabbitmq.Connect(strIP, iPort, strUser, strPasswd);
    printf("Rabbitmq Connect Ret: %d\n", iRet);


    std::string strExchange = "ExchangeTest";
    std::string strRoutekey = "routekeyTest";
    

    //// 可选操作 Declare Exchange
    //iRet = objRabbitmq.ExchangeDeclare(strExchange, "direct");
    //printf("Rabbitmq ExchangeDeclare Ret: %d\n", iRet);

    //// 可选操作（接收） Declare Queue
    //iRet = objRabbitmq.QueueDeclare(strQueuename);
    //printf("Rabbitmq QueueDeclare Ret: %d\n", iRet);

    //// 可选操作（接收） Queue Bind
    //iRet = objRabbitmq.QueueBind(strQueuename, strExchange, strRoutekey);
    //printf("Rabbitmq QueueBind Ret: %d\n", iRet);

    // Send Msg
    //std::string strSendMsg1 = "rabbitmq send test msg1";
    //std::string strSendMsg2 = "rabbitmq send test msg2";
    //iRet = objRabbitmq.Publish(strSendMsg1, strExchange, strRoutekey);
    //printf("Rabbitmq Publish 1 Ret: %d\n", iRet);
    //iRet = objRabbitmq.Publish(strSendMsg2, strExchange, strRoutekey);
    //printf("Rabbitmq Publish 2 Ret: %d\n", iRet);

    // Recv Msg
    

    thread t1(RecvData, &objRabbitmq);
    t1.detach();

    thread t2(CoutData);
    t2.detach();

    while(1)
    {
    }

    return 0;
}