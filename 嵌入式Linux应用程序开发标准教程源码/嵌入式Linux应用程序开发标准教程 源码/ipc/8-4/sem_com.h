
/* sem_com.h */

#ifndef		SEM_COM_H
#define		SEM_COM_H

#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int init_sem(int, int);
int del_sem(int);
int sem_p(int);
int sem_v(int); 

#endif /* SEM_COM_H */