//1. write a simple "Hello, world!" kernel module, extend your kernel module to print the following information to the kernel log:The name and PID of the current process (2 marks).The name and PID of the parent process (4 marks).Extend your kernel module to walk the process tree, starting from the current process, until you reach the process with pid 0 (10marks)


#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>


MODULE_AUTHOR("Mandar");
MODULE_DESCRIPTION("This is Hello Module programming");
MODULE_LICENSE("GPL");


static int Hello_init(void)

{

	printk("Hello Mandar pid=%d\n",current->pid);

	return 0;

}

static  void Hello_exit(void)
{
	printk("Bye Module Exit\n");
}

module_init(Hello_init);
module_exit(Hello_exit);
