/* waitpid.c */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pc, pr;
	
	pc = fork();
	if (pc < 0)
	{
		printf("Error fork\n");
	}
	else if (pc == 0) /*�ӽ���*/
	{ 
		/*�ӽ�����ͣ5s*/
		sleep(5);
		
		/*�ӽ��������˳�*/
		exit(0);
	}
	else /*������*/
	{
		/*ѭ�������ӽ����Ƿ��˳�*/
		do
		{
			/*����waitpid���Ҹ����̲�����*/
			pr = waitpid(pc, NULL, WNOHANG);
			
			/*���ӽ��̻�δ�˳����򸸽�����ͣ1s*/
			if (pr == 0)
			{
				printf("The child process has not exited\n");
				sleep(1);
			}
		} while (pr == 0);
		
		/*�������ӽ����˳�����ӡ����Ӧ���*/
		if (pr == pc)
		{
			printf("Get child exit code: %d\n",pr);
		}
		else
		{
			printf("Some error occured.\n");
		}
	}
	
	return 0;
}
