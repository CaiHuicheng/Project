
/* shmem.c */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 2048

int main()
{
	pid_t pid;
	int shmid;
	char *shm_addr;
	char flag[] = "WROTE";
	char *buff;
	
	/* ���������ڴ� */
	if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666)) < 0)
	{
		perror("shmget");
		exit(1);
	}
	else
	{
		printf("Create shared-memory: %d\n",shmid);
	}
	
	/* ��ʾ�����ڴ���� */
	system("ipcs -m");
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0) /* �ӽ��̴��� */
	{
		/*ӳ�乲���ڴ�*/
		if ((shm_addr = shmat(shmid, 0, 0)) == (void*)-1)
		{
			perror("Child: shmat");
			exit(1);
		}
		else
		{
			printf("Child: Attach shared-memory: %p\n", shm_addr);
		}
		system("ipcs -m");
		
		/* ͨ������ڹ����ڴ��ͷ���Ƿ��־�ַ���"WROTE"��ȷ�ϸ������Ѿ������ڴ�д����Ч���� */
		while (strncmp(shm_addr, flag, strlen(flag)))
		{
			printf("Child: Wait for enable data...\n");
			sleep(5);
		}
		
		/* ��ȡ�����ڴ����Ч���ݲ���ʾ */
		strcpy(buff, shm_addr + strlen(flag));
		printf("Child: Shared-memory :%s\n", buff);
		
		/* ��������ڴ�ӳ�� */
		if ((shmdt(shm_addr)) < 0)
		{
			perror("shmdt");
			exit(1);
		}
		else
		{
			printf("Child: Deattach shared-memory\n");
		}
		
	  	system("ipcs -m");
	  	
	  	if (shmctl(shmid, IPC_RMID, NULL) == -1)
		{
			perror("Child: shmctl(IPC_RMID)\n");
			exit(1);
		}
		else
		{
			printf("Delete shared-memory\n");
		}
		
		system("ipcs -m");
	}
	else /* �����̴��� */
	{
		/*ӳ�乲���ڴ�*/
		if ((shm_addr = shmat(shmid, 0, 0)) == (void*)-1)
		{
			perror("Parent: shmat");
			exit(1);
		}
		else
		{
			printf("Parent: Attach shared-memory: %p\n", shm_addr);
		}
		
		sleep(1);
		printf("\nInput some string:\n");
		fgets(buff, BUFFER_SIZE, stdin);
		strncpy(shm_addr + strlen(flag), buff, strlen(buff));
		strncpy(shm_addr, flag, strlen(flag));
		
		/* ��������ڴ�ӳ�� */
		if ((shmdt(shm_addr)) < 0)
		{
			perror("Parent: shmdt");
			exit(1);
		}
		else
		{
			printf("Parent: Deattach shared-memory\n");
		}
		system("ipcs -m");
		
		waitpid(pid, NULL, 0);		
		printf("Finished\n");
	}

  	exit(0);
}