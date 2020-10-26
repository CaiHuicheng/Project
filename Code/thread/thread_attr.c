#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUMBER		1
#define REPEAT_NUMBER		3
#define DELAY_TIME_LEVELS	10.0
int finish_flag = 0;

void * thrd_func(void * arg)
{
	int delay_time = 0;
	int count = 0;
	
	printf("Thread is starting\n");
	
	for (count = 0; count < REPEAT_NUMBER; count++)
	{
		
		delay_time = (int)(rand() * DELAY_TIME_LEVELS/(RAND_MAX)) + 1;
		sleep(delay_time);
		printf("\tThread : job %d delay = %d\n", count, delay_time);
	}

	printf("Thread finished\n");
	finish_flag = 1;
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t thread;
	pthread_attr_t attr;
	int res = 0;
	
	srand(time(NULL));
	
	res = pthread_attr_init(&attr);
	if (res != 0)
	{
		printf("Create attribute failed\n");
		exit(res);
	}
	
	res = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	res += pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	if (res != 0)
	{
		printf("Setting attribute failed\n");
		exit(res);
	}
	
	res = pthread_create(&thread, &attr, thrd_func, NULL);
	if (res != 0)
	{
		printf("Create thread failed\n");
		exit(res);
	}
	
	pthread_attr_destroy(&attr);
	printf("Create tread success\n");
	
	while(!finish_flag)
	{
		printf("Waiting for thread to finish...\n");
		sleep(2);
	}
	return 0;        
}