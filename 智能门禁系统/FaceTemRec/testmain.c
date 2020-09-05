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

    char *dev_name = "/dev/ttyUSB0";//根据实际情况选择串口

    while(1) 
    {  
        fd = OpenDev(dev_name); //打开串口 

        if(fd>0)
        {
            set_speed(fd,9600); //设置波特率
            printf("set speed success!\n");
        }     
        else  
        { 
            printf("Can't Open Serial Port!\n"); 
            sleep(1);  //休眠1s
            continue; 
        } 
        break;
    }

    if(set_Parity(fd,8,1,'N')==FALSE) //设置校验位 
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
        usleep(10000);  //休眠1ms
        nread = read(fd , phandle.buff + phandle.rxbuffsize, MAX_BUFF_SIZE - phandle.rxbuffsize);
        phandle.rxbuffsize += nread;
        phandle.buff[phandle.rxbuffsize] = '\0';
		/*
		处理 phandle.buff
		*/
	}

	return 0;
}

