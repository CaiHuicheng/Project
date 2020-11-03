
#ifndef _AMQPCLIENT_H
#define _AMQPCLIENT_H
 
#include "amqp.h"
 
class AmqpClient
{
public:
    AmqpClient(const char* hostname, const int port, const char* user, const char* pwd, 
    const char* vhost, const char* queuename);
    bool ConnectRabbitmq();
    bool StartConsumer();
    void CloseConnect();
private:
    amqp_connection_state_t conn = NULL;
    char m_hostname[128];
    int  m_port;
    char m_user[128];
    char m_pwd[128];
    char m_vhost[128];
    char m_queuename[128];
};
 
#endif