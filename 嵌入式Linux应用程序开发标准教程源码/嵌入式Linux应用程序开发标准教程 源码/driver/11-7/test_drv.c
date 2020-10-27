
/* test_drv.c */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#define 	TEST_DEVICE_NAME	"test_dev"
#define		BUFF_SZ			1024

/*ȫ�ֱ���*/
static struct cdev test_dev;
unsigned int major =0;
static char *data = NULL;

/*��������*/
static ssize_t test_read(struct file *file, char *buf, size_t count, loff_t *f_pos);
static ssize_t test_write(struct file *file,const char *buffer, size_t count,loff_t *f_pos);
static int test_open(struct inode *inode, struct file *file);
static int test_release(struct inode *inode,struct file *file);

/*������*/
static ssize_t test_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
	int len;
	if (count < 0 )
	{
		return -EINVAL;
	}
	len = strlen(data);
	count = (len > count)?count:len;
	if (copy_to_user(buf, data, count))
	{
		return -EFAULT;
	}
	return count;
}

/*д����*/
static ssize_t test_write(struct file *file, const char *buffer, size_t count, loff_t *f_pos)
{
	if(count < 0)
	{
		return -EINVAL;
	}
	memset(data, 0, BUFF_SZ);
	count = (BUFF_SZ > count)?count:BUFF_SZ;
	if (copy_from_user(data, buffer, count))
	{
		return -EFAULT;
	}
	return count;
}

/*�򿪺���*/
static int test_open(struct inode *inode, struct file *file)
{
	printk("This is open operation\n");
	data = (char*)kmalloc(sizeof(char) * BUFF_SZ, GFP_KERNEL);
	if (!data)
	{
		return -ENOMEM;
	}
	memset(data, 0, BUFF_SZ);
	return 0;
}

/*�رպ���*/
static int test_release(struct inode *inode,struct file *file)
{
	printk("This is release operation\n");
	if (data)
	{
		kfree(data);
		data = NULL;
	}
	return 0;
}

static void test_setup_cdev(struct cdev *dev, int minor,
		struct file_operations *fops)
{
	int err, devno = MKDEV(major, minor);
    
	cdev_init(dev, fops);
	dev->owner = THIS_MODULE;
	dev->ops = fops;
	err = cdev_add (dev, devno, 1);
	if (err)
	{
		printk (KERN_NOTICE "Error %d adding test %d", err, minor);
	}
}

/* tests�豸��file_operations�ṹ */
static struct file_operations test_fops = 
{
	.owner	 = THIS_MODULE,
	.read	 = test_read,
	.write	 = test_write,
	.open	 = test_open,
	.release = test_release,
};

/*ģ��ע�����*/
int init_module(void)
{
	int result;
	dev_t dev = MKDEV(major, 0);

	if (major)
	{
		result = register_chrdev_region(dev, 1, TEST_DEVICE_NAME);
	}
	else 
	{
		result = alloc_chrdev_region(&dev, 0, 1, TEST_DEVICE_NAME);
		major = MAJOR(dev);
	}

	if (result < 0) 
	{
		printk(KERN_WARNING "Test device: unable to get major %d\n", major);
		return result;
	}

	test_setup_cdev(&test_dev, 0, &test_fops);
	printk("The major of the test device is %d\n", major);
	return 0;
}

/*ж��ģ��*/
void cleanup_module(void) 
{
	cdev_del(&test_dev);
	unregister_chrdev_region(MKDEV(major, 0), 1);
	printk("Test device uninstalled\n");
}