//write a hello world module


#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>

MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Hello World Template module");
MODULE_LICENSE("GPLV2");

static int hello_init(void)
{
	
	printk("pid:%d app name:%s\n",current->pid,current->comm);
	printk(KERN_DEBUG "%s:%s:%d\n",__FILE__,__func__,__LINE__);
	//return -1;// module not loaded
	return 0; // module loaded
}

static void hello_exit(void)
{
	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);

}

module_init(hello_init); //module initialization 
module_exit(hello_exit);
