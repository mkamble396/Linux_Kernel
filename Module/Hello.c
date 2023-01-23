#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>


MODULE_AUTHOR("Kernel Master");
MODULE_DESCRIPTION("This Module programming");
MODULE_LICENSE("GPL");


static int Hello_init(void)

{

	printk("Hello Mandar It is Module Initialization\n");

	return 0;

}

static  void Hello_exit(void)
{
	printk("Bye Module Exit\n");
}

module_init(Hello_init);
module_exit(Hello_exit);
