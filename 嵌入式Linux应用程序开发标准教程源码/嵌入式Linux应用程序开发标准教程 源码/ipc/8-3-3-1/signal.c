
/* signal.c */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*自定义信号处理函数*/
void my_func(int sign_no)
{
	if (sign_no == SIGINT)
	{
		printf("I have get SIGINT\n");
	}	
  	else if (sign_no == SIGQUIT)
  	{
  		printf("I have get SIGQUIT\n");
  	}
}

int main()
{
	printf("Waiting for signal SIGINT or SIGQUIT...\n");
	
	/* 发出相应的信号，并跳转到信号处理函数处 */
	signal(SIGINT, my_func);
	signal(SIGQUIT, my_func);
	pause();
	exit(0);
}