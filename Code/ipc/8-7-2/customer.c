
/* customer.c */

#include "shm_com.h"
#include "sem_com.h"

int main()
{
	void *shared_memory = NULL;
	struct shm_buff *shm_buff_inst;
	int shmid, semid;

	/* ����ź��� */
	semid = semget(ftok(".", 'a'),  1, 0666);
	if (semid == -1)
	{	
		perror("Producer is'nt exist");
		exit(1);
	}
	
	/* ��ù����ڴ� */
	shmid = shmget(ftok(".", 'b'), sizeof(struct shm_buff), 0666|IPC_CREAT);
	if (shmid == -1)
	{
		perror("shmget");
		exit(1);
	}
	
	/* �������ڴ��ַӳ�䵽��ǰ���̵�ַ�ռ� */
	shared_memory = shmat(shmid, (void*)0, 0); 
	if (shared_memory == (void*)-1)
	{
		perror("shmat");
		exit(1);
	}
	printf("Memory attached at %X\n", (int)shared_memory);
	/* ��ù����ڴ��ӳ���ַ */
	shm_buff_inst = (struct shm_buff *)shared_memory;
		
	do
	{
		sem_p(semid);
		printf("Shared memory was written by process %d :%s", shm_buff_inst->pid, shm_buff_inst->buffer);
		if (strncmp(shm_buff_inst->buffer, "quit", 4) == 0) 
		{
			break;
		}
		shm_buff_inst->pid = 0;
		memset(shm_buff_inst->buffer, 0, SHM_BUFF_SZ);
		sem_v(semid);
	} while(1);

	/* ɾ�������ڴ浽��ǰ���̵�ַ�ռ��е�ӳ�� */
	if (shmdt(shared_memory) == -1)
	{
		perror("shmdt");
		exit(1);
	}

	/* ɾ�������ڴ� */
	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("shmctl(IPC_RMID)");
		exit(1);
	}
	exit(0);
}