
/* gpio_test.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "gpio_drv.h"

int led_timer(int dev_fd, int led_no, unsigned int time)
{
	led_no %= 4;
	ioctl(dev_fd, LED_D09_SWT + led_no, LED_SWT_ON);
	sleep(time);
	ioctl(dev_fd, LED_D09_SWT + led_no, LED_SWT_OFF);
}

int beep_timer(int dev_fd, unsigned int time)
{
	ioctl(dev_fd, BEEP_SWT, BEEP_SWT_ON);
	sleep(time);
	ioctl(dev_fd, BEEP_SWT, BEEP_SWT_OFF);	
}

int main()
{
	int i = 0;
	int dev_fd;
	dev_fd = open(GPIO_DEVICE_FILENAME, O_RDWR | O_NONBLOCK);

	if ( dev_fd == -1 ) 
	{
		printf("Cann't open gpio device file\n");
		exit(1);
	}

	while(1)
	{
		i = (i + 1) % 4;
		led_timer(dev_fd, i, 1);
		beep_timer(dev_fd, 1);		
	}

	close(dev_fd);
	return 0;
}