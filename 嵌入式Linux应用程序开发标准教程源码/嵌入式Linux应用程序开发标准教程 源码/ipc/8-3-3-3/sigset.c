/* sigset.c */
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*�Զ�����źŴ�����*/
void my_func(int signum)
{
	printf("If you want to quit,please try SIGQUIT\n");
}

int main()
{
	sigset_t set,pendset;
	struct sigaction action1,action2;
	
	/* ��ʼ���źż�Ϊ�� */
	if (sigemptyset(&set) < 0)
	{
		perror("sigemptyset");
		exit(1);
	}	
		
	/* ����Ӧ���źż����źż� */
	if (sigaddset(&set, SIGQUIT) < 0)
	{
		perror("sigaddset");
		exit(1);
	}
	
	if (sigaddset(&set, SIGINT) < 0)
	{
		perror("sigaddset");
		exit(1);
	}
	
	if (sigismember(&set, SIGINT))
	{
		sigemptyset(&action1.sa_mask);
		action1.sa_handler = my_func;
		action1.sa_flags = 0;
		sigaction(SIGINT, &action1, NULL);
	}
	
	if (sigismember(&set, SIGQUIT))
	{
		sigemptyset(&action2.sa_mask);
		action2.sa_handler = SIG_DFL;
		action2.sa_flags = 0;
		sigaction(SIGQUIT, &action2,NULL);
	}
	
	/* �����źż������֣���ʱset�е��źŲ��ᱻ���ݸ����̣���ʱ���������״̬ */
	if (sigprocmask(SIG_BLOCK, &set, NULL) < 0)
	{
		perror("sigprocmask");
		exit(1);
	}
	else
	{
		printf("Signal set was blocked, Press any key!");
		getchar();
	}
	
	/* ���ź���������ɾ��set�е��ź� */
	if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0)
	{
		perror("sigprocmask");
		exit(1);
	}
	else
	{
		printf("Signal set is in unblock state\n");
	}
	
	while(1);
	exit(0);
}