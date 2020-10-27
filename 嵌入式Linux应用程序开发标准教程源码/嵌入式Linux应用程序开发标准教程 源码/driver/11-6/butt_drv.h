
/* butt_drv.h */

#ifndef     FS2410_BUTTON_SET_H
#define     FS2410_BUTTON_SET_H

#define BUTTONS_DEVICE_NAME 		"buttons"
#define BUTTONS_DEVICE_FILENAME 	"/dev/buttons"
#define MAX_COLUMN					4
#define MAX_ROW						4
#define	MAX_KEY_COUNT  				MAX_COLUMN * MAX_ROW									

typedef struct _st_key_info_matrix			/* 按键数据结构 */
{
	unsigned char	key_id;					/* 按键ID */
	unsigned int	irq_no;					/* 对应的中断号 */
	unsigned int	irq_gpio_port;			/* 对应的中断线的输入端口地址*/
	unsigned int	kscan_gpio_port;		/* 对应的KSCAN端口地址 */
} st_key_info_matrix;

typedef struct _st_key_buffer				/* 按键缓冲数据结构 */
{
	unsigned long jiffy[MAX_KEY_COUNT];		/* 按键时间, 如果读键时, 5秒钟以前的铵键作废*/
	unsigned char buf[MAX_KEY_COUNT];		/* 按键缓冲区 */
	unsigned int head,tail;					/* 按键缓冲区头和尾 */
} st_key_buffer;

#endif /* FS2410_BUTTON_SET_H */