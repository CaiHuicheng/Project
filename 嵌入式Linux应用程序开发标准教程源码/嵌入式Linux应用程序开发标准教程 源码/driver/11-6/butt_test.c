
/* butt_test.c */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <asm/delay.h>
#include "butt_drv.h"
#include "gpio_drv.h"

main()
{
	int butt_fd, gpios_fd, i;
	unsigned char key = 0x0;
	butt_fd = open(BUTTONS_DEVICE_FILENAME, O_RDWR); /* 打开按钮设备 */
	if (butt_fd == -1)
	{
		printf("Open button device button errr!\n");
		return 0;
	}
	
	gpios_fd = open(GPIO_DEVICE_FILENAME, O_RDWR); /* 打开gpio设备 */
	if (gpios_fd == -1)
	{
		printf("Open button device button errr!\n");
		return 0;
	}

	ioctl(butt_fd, 0);	/* 清空键盘缓冲区, 后面参数没有意义 */

	printf("Press No.16 key to exit\n"); 
	do
	{	
		if (read(butt_fd, &key, 1) <= 0) /* 读键盘设备，得到相应的键值 */
		{
			continue;
		}
	
		printf("Key Value = %d\n", key);
		for (i = 0; i < LED_NUM; i++)
		{
			if ((key & (1 << i)) != 0)
			{
				ioctl(gpios_fd, LED_D09_SWT + i, LED_SWT_ON);
			}
		}
		ioctl(gpios_fd, BEEP_SWT, BEEP_SWT_ON);

		sleep(1);
		for (i = 0; i < LED_NUM; i++)
		{
			ioctl(gpios_fd, LED_D09_SWT + i, LED_SWT_OFF);			
		}
		ioctl(gpios_fd, BEEP_SWT, BEEP_SWT_OFF);

	} while(key != 16);

	close(gpios_fd); 
	close(butt_fd);
	return 0;
}