#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include "export.h"

static int two_init(void)
{
        int ret;
//	leave_sem();
       ret = get_sem();
       /* if(ret == 0) {
                printk("module two got the semaphore\n");
                return 0;
        } else {
                printk("could not get the semaphore\n");
                return -EPERM;
        }*/
	printk("unlock\n");
}

static void two_exit(void)
{
        printk("module two leaving the semaphore\n");
        leave_sem();
}

module_init(two_init);
module_exit(two_exit);

MODULE_LICENSE("GPL");


