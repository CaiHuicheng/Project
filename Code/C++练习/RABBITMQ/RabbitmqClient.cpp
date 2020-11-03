#include "RabbitmqClient.h"



#include "RabbitmqClient.h"
#include <io.h>
#include <process.h>


CRabbitmqClient::CRabbitmqClient()
    : m_strHostname("")
    , m_iPort(0)
    , m_strUser("")
    , m_strPasswd("")
    , m_iChannel(1) //默认用1号通道，通道无所谓 
    , m_pSock(NULL)
    , m_pConn(NULL) {

}

CRabbitmqClient::~CRabbitmqClient() {
    if (NULL != m_pConn) {
        Disconnect();
        m_pConn = NULL;
    }
}

int CRabbitmqClient::Connect(const string &strHostname, int iPort, const string &strUser, const string &strPasswd) {
    m_strHostname = strHostname;
    m_iPort = iPort;
    m_strUser = strUser;
    m_strPasswd = strPasswd;

    m_pConn = amqp_new_connection();  //返回连接状态的指针
    if (NULL == m_pConn) {
        fprintf(stderr, "amqp new connection failed\n");
        return -1;
    }

    m_pSock = amqp_tcp_socket_new(m_pConn); //创建一个tcp套接字
    if (NULL == m_pSock) {
        fprintf(stderr, "amqp tcp new socket failed\n");
        return -2;
    }

    int status = amqp_socket_open(m_pSock, m_strHostname.c_str(), m_iPort);  //绑定ip和端口打开一个连接
    if (status<0) {
        fprintf(stderr, "amqp socket open failed\n");
        return -3;
    }

    // amqp_login(amqp_connection_state_t state,char const *vhost, int channel_max, int frame_max, int heartbeat, amqp_sasl_method_enum sasl_method, ..)
    if (0 != ErrorMsg(amqp_login(m_pConn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, m_strUser.c_str(), m_strPasswd.c_str()), "Logging in")) //用户名和密码登录mq
    {
        return -4;
    }

    return 0;
}

int CRabbitmqClient::Disconnect() {
    if (NULL != m_pConn) {
        if (0 != ErrorMsg(amqp_connection_close(m_pConn, AMQP_REPLY_SUCCESS), "Closing connection"))
            return -1;

        if (amqp_destroy_connection(m_pConn) < 0)
            return -2;

        m_pConn = NULL;
    }

    return 0;
}

int CRabbitmqClient::ExchangeDeclare(const string &strExchange, const string &strType) {
    amqp_channel_open(m_pConn, m_iChannel);

    amqp_bytes_t _exchange = amqp_cstring_bytes(strExchange.c_str());
    amqp_bytes_t _type = amqp_cstring_bytes(strType.c_str());
    int _passive = 0;
    int _durable = 0;      // 交换机是否持久化
    amqp_exchange_declare(m_pConn, m_iChannel, _exchange, _type, _passive, _durable, 0, 0, amqp_empty_table);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "exchange_declare")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -1;
    }

    amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
    return 0;
}

int CRabbitmqClient::QueueDeclare(const string &strQueueName) {
    if (NULL == m_pConn) {
        fprintf(stderr, "QueueDeclare m_pConn is null\n");
        return -1;
    }

    amqp_channel_open(m_pConn, m_iChannel);
    amqp_bytes_t _queue = amqp_cstring_bytes(strQueueName.c_str());
    int32_t _passive = 0;
    int32_t _durable = 0;
    int32_t _exclusive = 0;
    int32_t _auto_delete = 1;
    amqp_queue_declare(m_pConn, m_iChannel, _queue, _passive, _durable, _exclusive, _auto_delete, amqp_empty_table);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "queue_declare")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -1;
    }

    amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
    return 0;
}

int CRabbitmqClient::QueueBind(const string &strQueueName, const string &strExchange, const string &strBindKey) {
    if (NULL == m_pConn) {
        fprintf(stderr, "QueueBind m_pConn is null\n");
        return -1;
    }

    amqp_channel_open(m_pConn, m_iChannel);
    amqp_bytes_t _queue = amqp_cstring_bytes(strQueueName.c_str());
    amqp_bytes_t _exchange = amqp_cstring_bytes(strExchange.c_str());
    amqp_bytes_t _routkey = amqp_cstring_bytes(strBindKey.c_str());
    amqp_queue_bind(m_pConn, m_iChannel, _queue, _exchange, _routkey, amqp_empty_table);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "queue_bind")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -1;
    }

    amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
    return 0;
}

int CRabbitmqClient::QueueUnbind(const string &strQueueName, const string &strExchange, const string &strBindKey) {
    if (NULL == m_pConn) {
        fprintf(stderr, "QueueUnbind m_pConn is null\n");
        return -1;
    }

    amqp_channel_open(m_pConn, m_iChannel);
    amqp_bytes_t _queue = amqp_cstring_bytes(strQueueName.c_str());
    amqp_bytes_t _exchange = amqp_cstring_bytes(strExchange.c_str());
    amqp_bytes_t _routkey = amqp_cstring_bytes(strBindKey.c_str());
    amqp_queue_unbind(m_pConn, m_iChannel, _queue, _exchange, _routkey, amqp_empty_table);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "queue_unbind")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -1;
    }

    amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
    return 0;
}

int CRabbitmqClient::QueueDelete(const string &strQueueName, int iIfUnused) {
    if (NULL == m_pConn) {
        fprintf(stderr, "QueueDelete m_pConn is null\n");
        return -1;
    }

    amqp_channel_open(m_pConn, m_iChannel);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "open channel")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -2;
    }

    amqp_queue_delete(m_pConn, m_iChannel, amqp_cstring_bytes(strQueueName.c_str()), iIfUnused, 0);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "delete queue")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -3;
    }

    amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
    return 0;
}

int CRabbitmqClient::Publish(const string &strMessage, const string &strExchange, const string &strRoutekey) {
    if (NULL == m_pConn) {
        fprintf(stderr, "publish m_pConn is null, publish failed\n");
        return -1;
    }

    amqp_channel_open(m_pConn, m_iChannel);
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "open channel")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -2;
    }

    amqp_bytes_t message_bytes;
    message_bytes.len = strMessage.length();
    message_bytes.bytes = (void *)(strMessage.c_str());
    //fprintf(stderr, "publish message(%d): %.*s\n", (int)message_bytes.len, (int)message_bytes.len, (char *)message_bytes.bytes);

    /*
    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes(m_type.c_str());
    props.delivery_mode = m_durable;    // persistent delivery mode
    */

    amqp_bytes_t exchange = amqp_cstring_bytes(strExchange.c_str());
    amqp_bytes_t routekey = amqp_cstring_bytes(strRoutekey.c_str());

    //if (0 != amqp_basic_publish(m_pConn, m_iChannel, exchange, routekey, 0, 0, &props, message_bytes)) {
    if (0 != amqp_basic_publish(m_pConn, m_iChannel, exchange, routekey, 0, 0, NULL, message_bytes)) {
        fprintf(stderr, "publish amqp_basic_publish failed\n");
        if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "amqp_basic_publish")) {
            amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
            return -3;
        }
    }

    amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
    return 0;
}

bool bhave = false;

int CRabbitmqClient::Consumer(const string &strQueueName, string &message_array, int GetNum, struct timeval *timeout) {
    if (NULL == m_pConn) 
    {
        fprintf(stderr, "Consumer m_pConn is null, Consumer failed\n");
        return -1;
    }

    amqp_channel_open(m_pConn, m_iChannel);  //打开信道
    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "open channel"))  //返回打开信道的结果
    {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -2;
    }

    amqp_basic_qos(m_pConn, m_iChannel, 0, GetNum, 0);
    int ack = 1; // no_ack    是否需要确认消息后再从队列中删除消息
    amqp_bytes_t queuename = amqp_cstring_bytes(strQueueName.c_str());  //将c字符串转为amap_bytes_t类型的字符串
    amqp_basic_consume(m_pConn, m_iChannel, queuename, amqp_empty_bytes, 0, ack, 0, amqp_empty_table);

    if (0 != ErrorMsg(amqp_get_rpc_reply(m_pConn), "Consuming")) {
        amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
        return -3;
    }

    int hasget = 0;
    
    
    
    while (1) 
    {
        amqp_rpc_reply_t res;
        amqp_envelope_t envelope;
        amqp_maybe_release_buffers(m_pConn);

        res = amqp_consume_message(m_pConn, &envelope, timeout, 0);
        if (AMQP_RESPONSE_NORMAL != res.reply_type) 
        {
            /*fprintf(stderr, "Consumer amqp_channel_close failed\n");
            amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);

            if (0 == hasget)
                return -res.reply_type;
            else
                return 0;*/
            continue;
        }

        string str((char *)envelope.message.body.bytes, (char *)envelope.message.body.bytes + envelope.message.body.len);
        message_array = str;
        //int rtn = amqp_basic_ack(m_pConn, m_iChannel, envelope.delivery_tag, 1);


        amqp_destroy_envelope(&envelope);
        /*if (rtn != 0)
        {
            
            amqp_channel_close(m_pConn, m_iChannel, AMQP_REPLY_SUCCESS);
            return -4;
        }*/

        bhave = true;
        //GetNum--;
        //hasget++;
        //usleep(1);
    }

    return 0;
}

int CRabbitmqClient::ErrorMsg(amqp_rpc_reply_t x, char const *context) {
    switch (x.reply_type) {
    case AMQP_RESPONSE_NORMAL:
        return 0;

    case AMQP_RESPONSE_NONE:
        fprintf(stderr, "%s: missing RPC reply type!\n", context);
        break;

    case AMQP_RESPONSE_LIBRARY_EXCEPTION:
        fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
        break;

    case AMQP_RESPONSE_SERVER_EXCEPTION:
        switch (x.reply.id) {
        case AMQP_CONNECTION_CLOSE_METHOD: {
            amqp_connection_close_t *m = (amqp_connection_close_t *)x.reply.decoded;
            fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
                context, m->reply_code, (int)m->reply_text.len,
                (char *)m->reply_text.bytes);
            break;
        }
        case AMQP_CHANNEL_CLOSE_METHOD: {
            amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
            fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
                context, m->reply_code, (int)m->reply_text.len,
                (char *)m->reply_text.bytes);
            break;
        }
        default:
            fprintf(stderr, "%s: unknown server error, method id 0x%08X\n",
                context, x.reply.id);
            break;
        }
        break;
    }

    return -1;
}