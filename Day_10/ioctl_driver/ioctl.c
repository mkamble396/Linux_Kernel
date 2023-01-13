
#include"ioctl.h"

#define mem_size 1024

dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer;

static int __init chr_driver_init(void);
static void __exit chr_driver_exit(void);

static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf,size_t len, loff_t *off);
static ssize_t my_write(struct file *file, const char *buf,size_t len, loff_t *off);
static long km_ioctl (struct file * file, unsigned int cmd, unsigned long arg);

static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.unlocked_ioctl = km_ioctl,
	.release = my_release,
};

static int my_open(struct inode *inode, struct file *file)
{
	//creating physical memory
	if((kernel_buffer = kmalloc(mem_size,GFP_KERNEL))==0)
	{
		printk(KERN_INFO"Cannot allocate the memory to the kernel..\n");
		return -1;
	}
	printk(KERN_INFO"Device file opened\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	kfree(kernel_buffer);
	printk(KERN_INFO"Device file closed\n");
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,size_t len, loff_t *off)
{
	copy_to_user(buf,kernel_buffer,mem_size);
	printk(KERN_INFO"Data read : Done..\n");
	return mem_size;
}

static ssize_t my_write(struct file *file, const char *buf,size_t len, loff_t *off)
{
	copy_from_user(kernel_buffer,buf,mem_size);
	printk(KERN_INFO"Data is written succesfully\n");
	return len;
}

static long km_ioctl (struct file * file, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {

		case SET_BAUD_RATE:
			printk ("\n Setting the Baud Rate to %ld ", arg);
			break;
		case SET_DIRECTION_WRITE:
			printk ("\n The Direction is set to write");
			break;
 		case SET_NO_STOP_BITS:
			printk ("\n Setting the Num of Stop bits to %ld", arg);
			break;
		default:
			printk ("\nCommand Not Found");
			return (-EINVAL);
	}
	return 0;
}



static int __init chr_driver_init(void)
{
	//allocating major and minor no.
	if((alloc_chrdev_region(&dev,0,1,"my_Dev")) < 0)
	{
		printk(KERN_INFO"Can not allocate the major no..\n");
		return -1;
	}

	printk(KERN_INFO"Major = %d Minor = %d \n",MAJOR(dev),MINOR(dev));

	//creating cdev structure
	
	cdev_init(&my_cdev,&fops);

	//Adding character device to the system
	if((cdev_add(&my_cdev,dev,1)) < 0)
	{
		printk(KERN_INFO"Cannot add the device to the system..\n");
                goto r_class;
	}

	//creating struct class
	if((dev_class = class_create(THIS_MODULE,"my_class")) == NULL)
	{
		printk(KERN_INFO"Cannot create the struct class..\n");
                goto r_class;
	}

	//creating device
	if((device_create(dev_class,NULL,dev,NULL,"my_device")) == NULL)
	{
		printk(KERN_INFO"Cannot create the device..\n");
		goto r_device;
	}

	printk(KERN_INFO"Device driver insert done properly\n");
	return 0;

r_device:
	class_destroy(dev_class);

r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

void __exit chr_driver_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Device Driver is removed succesfully..\n");
}

module_init(chr_driver_init);
module_exit(chr_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DEEPESH");
MODULE_DESCRIPTION("The character device driver");

