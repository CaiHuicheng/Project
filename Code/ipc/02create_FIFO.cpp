#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
 
    if(access("./testfifo1",F_OK) == -1){
        if (mkfifo("testfifo1",777) < 0)  //创建一个有名管道 ，并且给他赋予所有权限
        {
            perror("mkfifo:");
            exit(-1);
        }
    }
    printf ("mkfifo testfifo1 ok \n");     
    return 0;
}