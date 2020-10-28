#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> //open
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
 
int main()
{
    int ret;
    int a = 0;
    char  buf[20] = "";
    const char* path = "./testfifo1";
    const int pre = O_WRONLY;
    ret = open(path,pre);
    if(ret == -1){
        perror("open error");
        exit(-1);
    }
 
    while(a < 10){
        fgets(buf,20,stdin);
        write(ret,buf,sizeof(buf));
        printf("write : %s\n",buf);
    }
 
    return 0; 
}