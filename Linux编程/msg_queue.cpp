#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "msg_def.h"

Queue_t MsgQueue;

int main(int argc, char* argv[])
{
    int ret;
    pthread_t thread1_id;
    pthread_t thread2_id;
    pthread_t thread3_id;
    pthread_t handler_thread_id;

    ret = MsgQueueInit((Queue_t*)&MsgQueue);
    if(ret != 0)
    {
        return -1;
    }

    if(pthread_create(&handler_thread_id, NULL, (void*)msg_handler, NULL))
    {
        printf("create handler thread fail!\n");
        return -1;
    }


    if(pthread_create(&thread1_id, NULL, (void*)msg_sender1, NULL))
    {
        printf("create thread1 fail!\n");
        return -1;
    }

    if(pthread_create(&thread2_id, NULL, (void*)msg_sender2, NULL))
    {
        printf("create thread2 fail!\n");
        return -1;
    }

    if(pthread_create(&thread3_id, NULL, (void*)msg_sender3, NULL))
    {
        printf("create thread3 fail!\n");
        return -1;
    }


    while(1)
    {
        sleep(1);
    }

    return 0;
}




int MsgQueueInit(Queue_t* Q)
{
    if(!Q)
    {
        printf("Invalid Queue!\n");
        return -1;
    }
    Q->rear = 0;
    Q->head = 0;
    sem_init(&Q->sem, 0, 1);
    return 0;
}

int MsgDeQueue(Queue_t* Q, Msg_t* msg)
{
    if(!Q)
    {
        printf("Invalid Queue!\n");
        return -1;
    }
    if(Q->rear == Q->head) //only one cosumer,no need to lock head
    {
        printf("Empty Queue!\n");
        return -1;
    }
    memcpy(msg, &(Q->data[Q->head]), sizeof(Msg_t));
    Q->head = (Q->head+1)%QUEUE_SIZE;
    return 0;

}

int MsgEnQueue(Queue_t* Q, Msg_t* msg)
{
    if(Q->head == (Q->rear+1)%QUEUE_SIZE)
    {
        printf("Full Queue!\n");
        return -1;
    }
    sem_wait(&Q->sem);
    memcpy(&(Q->data[Q->rear]), msg, sizeof(Msg_t));
    Q->rear = (Q->rear+1)%QUEUE_SIZE;
    sem_post(&Q->sem);
    return 0;
}

void msg_printer(Msg_t* msg)
{
    if(!msg)
    {
        return;
    }
    printf("%s: I have recieved a message!\n", __FUNCTION__);
    printf("%s: msgtype:%d   msg_src:%d  dst:%d\n\n",__FUNCTION__,msg->hdr.msg_type,msg->hdr.msg_src,msg->hdr.msg_dst);

}

int msg_send()
{

    Msg_t msg;
    msg.hdr.msg_type = GO_HOME;
    msg.hdr.msg_src = THREAD1;
    msg.hdr.msg_dst = HANDLER;
    return MsgEnQueue((Queue_t*)&MsgQueue, &msg);

}

void msg_handler()
{
    sleep(5);  //let's wait 5s when starts
    while(1)
    {
        Msg_t msg;
        memset(&msg, 0 ,sizeof(Msg_t));
        int res = MsgDeQueue((Queue_t*)&MsgQueue, &msg);
        if(res != 0)
        {
            sleep(10);
            continue;
        }
        msg_printer(&msg);
        sleep(1);
    }
}


void msg_sender1()
{
    int i = 0;
    while(1)
    {
        if(i > 10)
        {
            i = 0;
        }
        Msg_t msg;
        msg.hdr.msg_type = i++;
        msg.hdr.msg_src = THREAD1;
        msg.hdr.msg_dst = HANDLER;
        MsgEnQueue((Queue_t*)&MsgQueue, &msg);
        printf("%s: Thread1 send a message!\n",__FUNCTION__);
        sleep(1);
    }
}

void msg_sender2()
{
    int i = 0;
    while(1)
    {
        if(i > 10)
        {
            i = 0;
        }
        Msg_t msg;
        msg.hdr.msg_type = i++;
        msg.hdr.msg_src = THREAD2;
        msg.hdr.msg_dst = HANDLER;
        MsgEnQueue((Queue_t*)&MsgQueue, &msg);
        printf("%s: Thread2 send a message!\n",__FUNCTION__);
        sleep(1);
    }
}

void msg_sender3()
{
    int i = 0;
    while(1)
    {
        if(i > 10)
        {
            i = 0;
        }
        Msg_t msg;
        msg.hdr.msg_type = i++;
        msg.hdr.msg_src = THREAD3;
        msg.hdr.msg_dst = HANDLER;
        MsgEnQueue((Queue_t*)&MsgQueue, &msg);
        printf("%s: Thread3 send a message!\n",__FUNCTION__);
        sleep(1);
    }
}