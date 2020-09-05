#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "openDev.h"

int main()
{
    int fd;
    int nread;
    char buffer[MAX_BUFF_SIZE];

    serial_parse phandle;
    phandle.rxbuffsize = 0;

    char *dev_name = "/dev/ttyUSB0";//����ʵ�����ѡ�񴮿�

    while(1) 
    {  
        fd = OpenDev(dev_name); //�򿪴��� 

        if(fd>0)
        {
            set_speed(fd,9600); //���ò�����
            printf("set speed success!\n");
        }     
        else  
        { 
            printf("Can't Open Serial Port!\n"); 
            sleep(1);  //����1s
            continue; 
        } 
        break;
    }

    if(set_Parity(fd,8,1,'N')==FALSE) //����У��λ 
    {
        printf("Set Parity Error\n"); 
        exit(1);
    }
    else
    {
        printf("Set Parity Success!\n"); 
    }

    while(1) 
    { 
        usleep(10000);  //����1ms
        nread = read(fd , phandle.buff + phandle.rxbuffsize, MAX_BUFF_SIZE - phandle.rxbuffsize);
        phandle.rxbuffsize += nread;
        phandle.buff[phandle.rxbuffsize] = '\0';
		/*
		���� phandle.buff
		*/
	}

	return 0;
}

