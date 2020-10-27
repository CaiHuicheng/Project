/* alarm_pause.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	/*调用alarm定时器函数*/
	int ret = alarm(5);
	pause();
	printf("I have been waken up.\n",ret); /* 此语句不会被执行 */
}