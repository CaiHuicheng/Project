#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> //open
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
 
int main(){
    int ret,fd;
    char  buf[20] = "";
    const char* path = "./testfifo1";
    const int pre = O_RDONLY;
    fd = open(path,pre);
    if(ret == -1){
        perror("open error");
        exit(-1);
    }
    
    do{
        ret = read(fd,buf,sizeof(buf));
        printf("read : %s\n",buf);
    }while(ret > 0);
 
    return 0; 
}