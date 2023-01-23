#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h> 
#include <linux/fs.h> 
#include <linux/errno.h> 
#include <linux/types.h> 
#include <linux/proc_fs.h>
#include <linux/fcntl.h> 
#include <linux/uaccess.h> 

MODULE_LICENSE("GPL");

int memory_open(struct inode *inode, struct file *filp);
int memory_release(struct inode *inode, struct file *filp);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
static void memory_exit(void);
static int memory_init(void);


struct file_operations memory_fops = {
  .read = memory_read,
  .write =  memory_write,
  .open = memory_open,
  .release = memory_release
};
int memory_major = 61;

char *memory_buffer;

int memory_open(struct inode *inode, struct file *filp) 
{
	printk(KERN_DEBUG "%s:%s:%d\n",__FILE__,__func__,__LINE__);
	return 0;
}

 
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) 
{
	printk(KERN_INFO "%s:%s:%d,count:%d,*f_pos:%d\n",__FILE__,__func__,__LINE__,count,*f_pos);
	
	copy_to_user(buf,memory_buffer,1);

	if (*f_pos == 0) {
	    *f_pos+=1;
	    return 1;
	  } 
	else 
	  {
	    return 0;
	  }


}

ssize_t memory_write( struct file *filp, const char *buf, size_t count, loff_t *f_pos) 
{
	printk(KERN_INFO "%s:%s:%d count:%d *f_pos:%d\n",__FILE__,__func__,__LINE__,count,*f_pos);

	
	copy_from_user(memory_buffer,buf,1);
	return 1;
}


/* close */ 
int memory_release(struct inode *inode, struct file *filp) 
{
	printk(KERN_INFO "%s:%s:%d\n",__FILE__,__func__,__LINE__);
	return 0;
}


static int memory_init(void) 
{
	int result;
	
	result = register_chrdev(memory_major, "mychmemory", &memory_fops); /* Registering device */
	if (result < 0) 
	{
		printk("memory: cannot obtain major number %d\n", memory_major);
		return result;
	}

      	
	memory_buffer = kmalloc(1, GFP_KERNEL);
	if (!memory_buffer) {
	    result = -ENOMEM;
	    goto fail;
	}
	
	memset(memory_buffer, 0, 1);
	printk("Inserting memory module\n");

      	return 0;

	fail:
	    memory_exit();
	    return result;
}


static void memory_exit(void) 
{
	  
	  unregister_chrdev(memory_major, "mychmemory");
	
	  
	  if (memory_buffer) {
	    kfree(memory_buffer);
	  }
	  printk("Removing memory module\n");
}



module_init(memory_init);
module_exit(memory_exit);

