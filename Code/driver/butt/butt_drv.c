#include <linux/config.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/spinlock.h>

#include <asm/hardware.h>
#include <asm/delay.h>
#include <asm/uaccess.h>
#include <asm-arm/arch-s3c2410/regs-gpio.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm-arm/arch-s3c2410/irqs.h>
#include <asm-arm/irq.h>
#include <linux/config.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <asm/uaccess.h>
#include <asm/hardware.h>
#include <asm/arch/regs-gpio.h>
#include "butt_drv.h"

static st_key_info_matrix key_info_matrix[MAX_COLUMN][MAX_ROW] =
{
	{{10,	IRQ_EINT0,	S3C2410_GPF0,	S3C2410_GPE11},
	{11,	IRQ_EINT0,	S3C2410_GPF0,	S3C2410_GPG6},
	{12,	IRQ_EINT0,	S3C2410_GPF0,   S3C2410_GPE13},
	{16,	IRQ_EINT0,	S3C2410_GPF0,	S3C2410_GPG2}},
	
	{{7,	IRQ_EINT2,	S3C2410_GPF2,	S3C2410_GPE11},
	{8,	IRQ_EINT2,	S3C2410_GPF2,	S3C2410_GPG6},
	{9,	IRQ_EINT2,	S3C2410_GPF2,	S3C2410_GPE13},
	{15,	IRQ_EINT2,	S3C2410_GPF2,	S3C2410_GPG2}},
	
	{{4,	IRQ_EINT11,	S3C2410_GPG3,	S3C2410_GPE11},
	{5,	IRQ_EINT11,	S3C2410_GPG3,	S3C2410_GPG6},
	{6, 	IRQ_EINT11,	S3C2410_GPG3,	S3C2410_GPE13},
	{14,	IRQ_EINT11,	S3C2410_GPG3,	S3C2410_GPG2}},
	
	{{1,	IRQ_EINT19,	S3C2410_GPG11,	S3C2410_GPE11},
	{2,	IRQ_EINT19,	S3C2410_GPG11,	S3C2410_GPG6},
	{3, 	IRQ_EINT19,	S3C2410_GPG11,	S3C2410_GPE13},
	{13,    IRQ_EINT19,	S3C2410_GPG11,	S3C2410_GPG2}},
};

static st_key_buffer key_buffer;			/* 键盘缓冲区 */
static spinlock_t buffer_lock;				/*缓冲区锁 */
static int   button_major = 0;		

/* 获取当前的毫秒数(从系统启动开始）*/
static unsigned long get_tick_count(void)
{
	struct timeval currTick;
	unsigned long ulRet;

	do_gettimeofday(&currTick);
	ulRet = currTick.tv_sec;
	ulRet *= 1000;
	ulRet += (currTick.tv_usec + 500) / 1000;
	return ulRet;
}

/* 初始化键盘缓冲区 */
static void init_keybuffer(void)
{
	int i;

	spin_lock_irq(&buffer_lock); /* 获得一个自旋锁 */

	key_buffer.head = 0;
	key_buffer.tail = 0;
	for(i = 0; i < MAX_KEY_COUNT; i++)
	{
		key_buffer.buf[i] = 0;
		key_buffer.jiffy[i] = 0;
	}

	spin_unlock_irq(&buffer_lock); /* 释放自旋锁 */
}

/* 从缓冲删除过时数据(5秒前的按键值) */
static void remove_timeoutkey(void)
{
	unsigned long tick;

	spin_lock_irq(&buffer_lock); /* 获得一个自旋锁 */

	while(key_buffer.head != key_buffer.tail)
	{
		tick = get_tick_count() - key_buffer.jiffy[key_buffer.head];
		if (tick  < 5000)	/* 5秒 */
			break;
		key_buffer.buf[key_buffer.head] = 0;
		key_buffer.jiffy[key_buffer.head] = 0;
		key_buffer.head ++;
		key_buffer.head &= (MAX_KEY_COUNT -1);
	}

	spin_unlock_irq(&buffer_lock); /* 释放自旋锁 */
}

void s3c2410_gpio_cfgpin(unsigned int pin, unsigned int function)
{
	unsigned long base = S3C2410_GPIO_BASE(pin);
	unsigned long shift = 1;
	unsigned long mask = 0x03;
	unsigned long con;
	unsigned long flags;
	
	if (pin < S3C2410_GPIO_BANKB) 
	{   
		shift = 0;
		mask  = 0x01;
	}   
	
	mask <<= (S3C2410_GPIO_OFFSET(pin) << shift);
	
	local_irq_save(flags);
	
	con = __raw_readl(base + 0x00);
	con &= ~mask;
	con |= function;
	
	__raw_writel(con, base + 0x00);
	
	local_irq_restore(flags);
}

void s3c2410_gpio_setpin(unsigned int pin, unsigned int to) 
{
	unsigned long base = S3C2410_GPIO_BASE(pin);
	unsigned long offs = S3C2410_GPIO_OFFSET(pin);
	unsigned long flags;
	unsigned long dat;
	
	local_irq_save(flags);
	
	dat = __raw_readl(base + 0x04);
	dat &= ~(1 << offs);
	dat |= to << offs;
	__raw_writel(dat, base + 0x04);
	
	local_irq_restore(flags);
}

unsigned int s3c2410_gpio_getpin(unsigned int pin) 
{
	unsigned long base = S3C2410_GPIO_BASE(pin);
	unsigned long offs = S3C2410_GPIO_OFFSET(pin);
	unsigned long dat = 0;
	unsigned long flags;
	
	local_irq_save(flags);
	dat = __raw_readl(base + 0x04);
	local_irq_restore(flags);
	return ((dat & (1 << offs)) >> offs);
}

/* 初始化GPIO, 设置中断0, 2, 11, 19为下降沿中断 */
static void init_gpio(void)
{
	s3c2410_gpio_cfgpin(S3C2410_GPE11, S3C2410_GPE11_OUTP); /* GPE11 */
	s3c2410_gpio_setpin(S3C2410_GPE11, 0);
	s3c2410_gpio_cfgpin(S3C2410_GPE13, S3C2410_GPE13_OUTP); /* GPE13 */
	s3c2410_gpio_setpin(S3C2410_GPE13, 0);
	s3c2410_gpio_cfgpin(S3C2410_GPG2, S3C2410_GPG2_OUTP); /* GPG2 */
	s3c2410_gpio_setpin(S3C2410_GPG2, 0);
	s3c2410_gpio_cfgpin(S3C2410_GPG6, S3C2410_GPG6_OUTP); /* GPG6 */
	s3c2410_gpio_setpin(S3C2410_GPG6, 0);

	s3c2410_gpio_cfgpin(S3C2410_GPF0, S3C2410_GPF0_EINT0); /* GPF0 */
	s3c2410_gpio_cfgpin(S3C2410_GPF2, S3C2410_GPF2_EINT2); /* GPF2 */
	s3c2410_gpio_cfgpin(S3C2410_GPG3, S3C2410_GPG3_EINT11); /* GPG3 */
	s3c2410_gpio_cfgpin(S3C2410_GPG11, S3C2410_GPG11_EINT19); /* GPG11 */

	set_irq_type(IRQ_EINT0, IRQT_FALLING);
	set_irq_type(IRQ_EINT2, IRQT_FALLING);
	set_irq_type(IRQ_EINT11, IRQT_FALLING);
	set_irq_type(IRQ_EINT19, IRQT_FALLING);
}

/* 激活中断 */
static __inline void enable_irqs(void)
{
	int i;

	for (i = 0; i < MAX_COLUMN; i++)
	{
		enable_irq(key_info_matrix[i][0].irq_no);				
	}
}

/* 屏蔽中断 */
static __inline void disable_irqs(void)
{
	int i;

	for (i = 0; i < MAX_COLUMN; i++)
	{
		disable_irq(key_info_matrix[i][0].irq_no);				
	}
}

/* 
** 进入中断后, 扫描铵键码 
** 返回: 按键码(1-16), 0xff表示错误 
*/
static __inline unsigned char button_scan(int irq)
{
	unsigned char key_id = 0xff;
	unsigned char column = 0xff, row = 0xff;	
	
	s3c2410_gpio_cfgpin(S3C2410_GPF0, S3C2410_GPF0_INP); /* GPF0 */
	s3c2410_gpio_cfgpin(S3C2410_GPF2, S3C2410_GPF2_INP); /* GPF2 */
	s3c2410_gpio_cfgpin(S3C2410_GPG3, S3C2410_GPG3_INP); /* GPG3 */
	s3c2410_gpio_cfgpin(S3C2410_GPG11, S3C2410_GPG11_INP); /* GPG11 */
	
	switch (irq)
	{
		case IRQ_EINT0:
		{
			column = 0;
		}
		break;

		case IRQ_EINT2:
		{
			column = 1;
		}
		break;

		case IRQ_EINT11:
		{
			column = 2;
		}
		break;

		case IRQ_EINT19:
		{
			column = 3;
		}
		break;
	}
	
	if (column != 0xff)
	{
		s3c2410_gpio_setpin(S3C2410_GPE11, 0);
		s3c2410_gpio_setpin(S3C2410_GPG6, 1);
		s3c2410_gpio_setpin(S3C2410_GPE13, 1);
		s3c2410_gpio_setpin(S3C2410_GPG2, 1);
		if (!s3c2410_gpio_getpin(key_info_matrix[column][0].irq_gpio_port))
		{
			key_id = key_info_matrix[column][0].key_id;
			return key_id;
		}

		s3c2410_gpio_setpin(S3C2410_GPE11, 1);
		s3c2410_gpio_setpin(S3C2410_GPG6, 0);
		s3c2410_gpio_setpin(S3C2410_GPE13, 1);
		s3c2410_gpio_setpin(S3C2410_GPG2, 1);
		if (!s3c2410_gpio_getpin(key_info_matrix[column][1].irq_gpio_port))
		{
			key_id = key_info_matrix[column][1].key_id;
			return key_id;
		}

		s3c2410_gpio_setpin(S3C2410_GPE11, 1);
		s3c2410_gpio_setpin(S3C2410_GPG6, 1);
		s3c2410_gpio_setpin(S3C2410_GPE13, 0);
		s3c2410_gpio_setpin(S3C2410_GPG2, 1);
		if (!s3c2410_gpio_getpin(key_info_matrix[column][2].irq_gpio_port))
		{
			key_id = key_info_matrix[column][2].key_id;
			return key_id;
		}

		s3c2410_gpio_setpin(S3C2410_GPE11, 1);
		s3c2410_gpio_setpin(S3C2410_GPG6, 1);
		s3c2410_gpio_setpin(S3C2410_GPE13, 1);
		s3c2410_gpio_setpin(S3C2410_GPG2, 0);
		if (!s3c2410_gpio_getpin(key_info_matrix[column][3].irq_gpio_port))
		{
			key_id = key_info_matrix[column][3].key_id;
			return key_id;
		}
	}
	
	return key_id;
}

/* 中断处理函数,其中irq为中断号 */
static irqreturn_t button_irq(int irq, void *dev_id, struct pt_regs *regs)
{
	unsigned char ucKey = 0;

	disable_irqs();

	/* 延迟50毫秒, 屏蔽按键毛刺 */
	udelay(50000);
	ucKey = button_scan(irq);
	if ((ucKey >= 1) && (ucKey <= 16))
	{
		/* 如果缓冲区已满, 则不添加 */
		if (((key_buffer.head + 1) & (MAX_KEY_COUNT - 1)) != key_buffer.tail)
		{
			spin_lock_irq(&buffer_lock);
			key_buffer.buf[key_buffer.tail] = ucKey;
			key_buffer.jiffy[key_buffer.tail] = get_tick_count();
			key_buffer.tail ++;
			key_buffer.tail &= (MAX_KEY_COUNT -1);
			spin_unlock_irq(&buffer_lock);
		}
	}
	init_gpio();
	enable_irqs();

	return IRQ_HANDLED;/* 2.6内核返回值一般是这个宏 */
}

/* 申请中断函数 */
static  int request_irqs(void)
{
	int ret, i, j;

	for (i = 0; i < MAX_COLUMN; i++)
	{
		ret = request_irq(key_info_matrix[i][0].irq_no, button_irq, SA_INTERRUPT, BUTTONS_DEVICE_NAME, NULL);
		if (ret < 0)
		{
			for (j = 0; j < i; j++)
			{
				free_irq(key_info_matrix[j][0].irq_no, NULL);				
			}
			return -EFAULT;
		}
	}
	return 0;
}

/* 释放中断 */
static __inline void free_irqs(void)
{
	int i;

	for (i = 0; i < MAX_COLUMN; i++)
	{
		free_irq(key_info_matrix[i][0].irq_no, NULL);				
	}
}

/* 打开文件, 申请中断 */
static int button_open(struct inode *inode,struct file *filp) 
{
	int ret = nonseekable_open(inode, filp);
	if (ret < 0)
	{
		return ret;
	}

	init_gpio();
	ret = request_irqs();
	if (ret < 0) 
	{
		return ret;
	}

	init_keybuffer();

	return ret;
}

/* 关闭文件, 屏蔽中断 */
static int button_release(struct inode *inode,struct file *filp)
{
	free_irqs();
    return 0;
}

/* 读键盘 */
static ssize_t button_read(struct file *filp, char *buffer, size_t count, loff_t *f_pos)
{
	ssize_t ret = 0;

	remove_timeoutkey();
	spin_lock_irq(&buffer_lock);
	while((key_buffer.head != key_buffer.tail) && (((size_t)ret) < count) )
	{
		put_user((char)(key_buffer.buf[key_buffer.head]), &buffer[ret]);
		key_buffer.jiffy[key_buffer.head] = 0;
		key_buffer.head ++;
		key_buffer.head &= (MAX_KEY_COUNT -1);
		ret ++;
	}
	spin_unlock_irq(&buffer_lock);
	return ret;
}

/* 清空键盘缓冲区 */
static int button_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	init_keybuffer();
	return 0;
}

/* 初始化并添加结构提struct cdev到系统之中 */
static void button_setup_cdev(struct cdev *dev,int minor,struct file_operations *fops)
{
	int err;
	int devno = MKDEV(button_major,minor);

	cdev_init(dev, fops); /* 初始化结构体struct cdev */
	dev->owner = THIS_MODULE;
	dev->ops = fops; /* 给结构体里的ops成员赋初值，这里是对设备操作的具体的实现函数 */
	err = cdev_add(dev, devno, 1); /* 将结构提struct cdev添加到系统之中 */
	if (err)
	{
		printk(KERN_INFO"Error %d adding button %d\n",err, minor);
	}
}
/*
 *定义一个file_operations结构体，来实现对设备的具体操作的功能
 */
static struct file_operations button_fops =
{
	.owner = THIS_MODULE,
	.ioctl = button_ioctl,
	.open = button_open,
	.read = button_read,
	.release = button_release,
};

static struct cdev button_dev;

/* 驱动初始化 */
static int  button_init(void)
{
	int ret; 

	dev_t dev = MKDEV(button_major, 0); /* 将主设备号和次设备号定义到一个dev_t数据类型的结构体之中 */
	if (button_major)
	{
		ret = register_chrdev_region(dev, 1, BUTTONS_DEVICE_NAME);/* 静态注册一个设备，设备号先前指定好，并得到一个设备名，cat /proc/device来查看信息 */
	}
	else
	{
		ret = alloc_chrdev_region(&dev, 0, 1, BUTTONS_DEVICE_NAME);/* 如果主设备号被占用，则由系统提供一个主设备号给设备驱动程序 */
		button_major = MAJOR(dev); /* 获得主设备号 */
	}

	if (ret < 0)
	{
		printk(KERN_WARNING"Button:unable to get major %d\n",button_major);		
		return ret;
	}

	button_setup_cdev(&button_dev, 0, &button_fops); /* 初始化和添加结构体struct cdev到系统之中 */
	printk("Button driver initialized.\n");
	return 0;
}

/* 驱动卸载 */
static void __exit button_exit(void)
{
	cdev_del(&button_dev); /* 删除结构体struct cdev */
	unregister_chrdev_region(MKDEV(button_major, 0), 1); /* 卸载设备驱动所占有的资源 */
	printk("Button driver uninstalled\n");
}

module_init(button_init); /* 初始化设备驱动程序的入口 */
module_exit(button_exit); /* 卸载设备驱动程序的入口 */
MODULE_AUTHOR("David");
MODULE_LICENSE("Dual BSD/GPL");