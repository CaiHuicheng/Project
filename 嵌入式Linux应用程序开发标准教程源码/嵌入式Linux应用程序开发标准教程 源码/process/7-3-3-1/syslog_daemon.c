/* syslog_daemon.c利用syslog服务的守护进程实例 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <syslog.h>

int main()
{
	pid_t pid, sid;
	int   i, fd;
	char  *buf = "This is a Dameon\n";
	
	pid = fork(); /* 第一步 */
	if (pid < 0)
	{
		printf("Error fork\n");
		exit(1);
	}
	else if (pid > 0)
	{
		exit(0); /* 父进程推出 */
	}
	
	openlog("daemon_syslog", LOG_PID, LOG_DAEMON); /* 打开系统日志服务，openlog */
	
	if ((sid = setsid()) < 0) /*第二步*/
	{
		syslog(LOG_ERR, "%s\n", "setsid");
		exit(1);
	}
	
	if ((sid = chdir("/")) < 0) /*第三步*/
	{
		syslog(LOG_ERR, "%s\n", "chdir");
		exit(1);
	}
	
	umask(0); /*第四步*/
	
	for(i = 0; i < getdtablesize(); i++) /*第五步*/
	{
		close(i);
	}
	
	/*这时创建完守护进程，以下开始正式进入守护进程工作*/
	while(1)
	{
		if ((fd = open("/tmp/daemon.log", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
		{
			syslog(LOG_ERR, "open");
			exit(1);
		}
		
		write(fd, buf, strlen(buf) + 1);
		close(fd);
		sleep(10);
	}
	
	closelog();
	exit(0);
}