/* alarm_pause.c */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	/*����alarm��ʱ������*/
	int ret = alarm(5);
	pause();
	printf("I have been waken up.\n",ret); /* ����䲻�ᱻִ�� */
}