#include <linux/config.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>   //printk()
#include <linux/slab.h>		// kmalloc() 
#include <linux/fs.h>       // everything...
#include <linux/errno.h>    // error codes
#include <linux/types.h>    //size_t 
#include <linux/mm.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/arch-s3c2410/regs-gpio.h>
#include "gpio_drv.h"

static int major = 0;
module_param(major, int, 0);

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

void s3c2410_gpio_pullup(unsigned int pin, unsigned int to) 
{
	unsigned long base = S3C2410_GPIO_BASE(pin);
	unsigned long offs = S3C2410_GPIO_OFFSET(pin);
	unsigned long flags;
	unsigned long up; 
	
	
	if (pin < S3C2410_GPIO_BANKB)
	{
		return;
	}
	
	local_irq_save(flags);
	
	up = __raw_readl(base + 0x08);
	up &= ~(1 << offs);
	up |= to << offs;
	__raw_writel(up, base + 0x08);
	
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


int gpio_open (struct inode *inode, struct file *filp)
{
	s3c2410_gpio_pullup(S3C2410_GPB0, 1); // BEEP
	s3c2410_gpio_pullup(S3C2410_GPF4, 1); // LED D12
	s3c2410_gpio_pullup(S3C2410_GPF5, 1); // LED D11 	
	s3c2410_gpio_pullup(S3C2410_GPF6, 1); // LED D10 
	s3c2410_gpio_pullup(S3C2410_GPF7, 1); // LED D9 	
	s3c2410_gpio_cfgpin(S3C2410_GPB0, S3C2410_GPB0_OUTP);
	s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF4_OUTP);
	s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF5_OUTP);
	s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF6_OUTP);
	s3c2410_gpio_cfgpin(S3C2410_GPF4, S3C2410_GPF7_OUTP);
	return 0;
}

ssize_t gpio_read(struct file *file, char __user *buff, size_t count, loff_t *offp)
{
	return 0;
}

ssize_t gpio_write(struct file *file, const char __user *buff, size_t count, loff_t *offp)
{
	return 0;
}

int switch_gpio(unsigned int pin, unsigned int swt)
{
	if (!((pin <= S3C2410_GPF7) && (pin >= S3C2410_GPF4)) && (pin != S3C2410_GPB0))
	{
		printk("Unsupported pin");
		return 1; 
	}
	s3c2410_gpio_setpin(pin, swt);
	return 0;
}

static int gpio_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	unsigned int swt = (unsigned int)arg;
	switch (cmd) 
	{
		case LED_D09_SWT:
		{
			switch_gpio(S3C2410_GPF7, swt);	
		}
		break;

		case LED_D10_SWT:
		{
			switch_gpio(S3C2410_GPF6, swt);			
		}
		break;

		case LED_D11_SWT:
		{
			switch_gpio(S3C2410_GPF5, swt);			
		}
		break;
		case LED_D12_SWT:
		{
			switch_gpio(S3C2410_GPF4, swt);			
		}
		break;

		case BEEP_SWT:
		{
			switch_gpio(S3C2410_GPB0, swt);
			break;
		}

		default:
		{
			printk("Unsupported command\n");
			break;
		}
	}
	return 0;
}

static int gpio_release(struct inode *node, struct file *file)
{
	switch_gpio(S3C2410_GPB0, BEEP_SWT_OFF);
	switch_gpio(S3C2410_GPF4, LED_SWT_OFF);
	switch_gpio(S3C2410_GPF5, LED_SWT_OFF);
	switch_gpio(S3C2410_GPF6, LED_SWT_OFF);
	switch_gpio(S3C2410_GPF7, LED_SWT_OFF);
	return 0;
}

/*
 * Set up the cdev structure for a device.
 */
static void gpio_setup_cdev(struct cdev *dev, int minor,
		struct file_operations *fops)
{
	int err, devno = MKDEV(major, minor);
    
	cdev_init(dev, fops);
	dev->owner = THIS_MODULE;
	dev->ops = fops;
	err = cdev_add (dev, devno, 1);
	if (err)
	{
		printk (KERN_NOTICE "Error %d adding gpio %d", err, minor);
	}
}

static struct file_operations gpio_fops = 
{
	.owner   = THIS_MODULE,
	.open    = gpio_open,
	.release = gpio_release,
	.read    = gpio_read,
	.write   = gpio_write,
	.ioctl   = gpio_ioctl,	
};

static struct cdev gpio_devs;

static int gpio_init(void)
{
	int result;
	dev_t dev = MKDEV(major, 0);

	if (major)
	{
		result = register_chrdev_region(dev, 1, GPIO_DEVICE_NAME);
	}
	else 
	{
		result = alloc_chrdev_region(&dev, 0, 1, GPIO_DEVICE_NAME);
		major = MAJOR(dev);
	}

	if (result < 0) 
	{
		printk(KERN_WARNING "Gpio: unable to get major %d\n", major);
		return result;
	}

	gpio_setup_cdev(&gpio_devs, 0, &gpio_fops);
	printk("The major of the gpio device is %d\n", major);
	return 0;
}

static void gpio_cleanup(void)
{
	cdev_del(&gpio_devs);
	unregister_chrdev_region(MKDEV(major, 0), 1);
	printk("Gpio device uninstalled\n");
}

module_init(gpio_init);
module_exit(gpio_cleanup);
MODULE_AUTHOR("David");
MODULE_LICENSE("Dual BSD/GPL");