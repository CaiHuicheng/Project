
/* producer.c */

#include "shm_com.h"
#include "sem_com.h"
#include <signal.h>

int ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return 0;
}

int main()
{
	void *shared_memory = NULL;
	struct shm_buff *shm_buff_inst;
	char buffer[BUFSIZ];
	int shmid, semid;

	ignore_signal(); /* 防止程序非正常退出 */
	semid = semget(ftok(".", 'a'),  1, 0666|IPC_CREAT); /* 创建一个信号量*/
	init_sem(semid, 1);/* 初始值为1 */

	/* 创建共享内存 */
	shmid = shmget(ftok(".", 'b'), sizeof(struct shm_buff), 0666|IPC_CREAT);
	if (shmid == -1)
	{
		perror("shmget failed");
		del_sem(semid);
		exit(1);
	}
	
	/* 将共享内存地址映射到当前进程地址空间 */
	shared_memory = shmat(shmid, (void*)0, 0);
	if (shared_memory == (void*)-1)
	{
		perror("shmat");
		del_sem(semid);
		exit(1);
	}
	printf("Memory attached at %X\n", (int)shared_memory);
	/* 获得共享内存的映射地址 */
	shm_buff_inst = (struct shm_buff *)shared_memory;
	
	do
	{
		sem_p(semid);	
		printf("Enter some text to the shared memory(enter 'quit' to exit):");
		
		/* 向共享内存写入数据 */
		if (fgets(shm_buff_inst->buffer, SHM_BUFF_SZ, stdin) == NULL)
		{
			perror("fgets");
			sem_v(semid);
			break;
		}
		shm_buff_inst->pid = getpid();		
		sem_v(semid);
	} while(strncmp(shm_buff_inst->buffer, "quit", 4) != 0);

	/* 删除信号量 */
	del_sem(semid);
	
	/* 删除共享内存到当前进程地址空间中的映射 */
	if (shmdt(shared_memory) == 1)
	{
		perror("shmdt");
		exit(1);
	}
	exit(0);
}