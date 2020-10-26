
#ifndef 	FS2410_GPIO_SET_H
#define 	FS2410_GPIO_SET_H

#include 	<linux/ioctl.h>
#define		GPIO_DEVICE_NAME		"gpio"
#define		GPIO_DEVICE_FILENAME		"/dev/gpio"
#define		LED_NUM					4
#define 	GPIO_IOCTL_MAGIC		'G'
#define 	LED_D09_SWT			_IOW(GPIO_IOCTL_MAGIC, 0, unsigned int)
#define 	LED_D10_SWT			_IOW(GPIO_IOCTL_MAGIC, 1, unsigned int)
#define 	LED_D11_SWT			_IOW(GPIO_IOCTL_MAGIC, 2, unsigned int)
#define 	LED_D12_SWT			_IOW(GPIO_IOCTL_MAGIC, 3, unsigned int)
#define 	BEEP_SWT			_IOW(GPIO_IOCTL_MAGIC, 4, unsigned int)
#define		LED_SWT_ON			0
#define		LED_SWT_OFF			1
#define		BEEP_SWT_ON			1
#define		BEEP_SWT_OFF			0

#endif 