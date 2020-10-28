#include <iostream>
#include <unistd.h>
#include <stdio.h>
 
using namespace std;
 
int main()
{
    int f_pipe[2];
    //创建pipe
    if(pipe(f_pipe)<0){
        cout<<"pipe error"<<endl;
        exit(-1);
    }
 
    pid_t pid = fork();
 
    if(pid <0 ){
        cout<<"fork error"<<endl;
        close(f_pipe[0]);
        close(f_pipe[1]);
        exit(-1);
    }else if(pid ==0 ){
        //child process
        int a = 0;
        const int BUF = 20;
        char buf[BUF] = "";
        //子进程负责写 ， 所以关闭 f_pipe[0] 读端
        close(f_pipe[0]);
        while(a < 10){
            fgets(buf,BUF,stdin);
            if(write(f_pipe[1],buf,sizeof(buf)) < 0){
                cout<<"fork error"<<endl;
                exit(-1);
            }
            cout<<"child send : "<<buf<<endl;
            a++;
        }
    }else {
        //father process
        int b = 0;
        const int  FBUF = 20;
        char fbuf[FBUF] = "";
        //父进程负责读 ， 所以关闭 f_pipe[1] 写端
        close(f_pipe[1]);
        while(b < 10){
            read(f_pipe[0],fbuf,sizeof(fbuf));
            cout<<"father  recv: "<<fbuf<<endl;
            b++;
        }
    }
 
    return 0;
}