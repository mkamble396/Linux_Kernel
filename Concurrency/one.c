#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include "export.h"


 static int one_init(void)
{
        int ret;
        ret = get_sem();
        if(ret == 0) {
                printk("module one got the semaphore\n");
                return 0;
        } else {
                printk("could not get the semaphore\n");
                return -EPERM;
        }
}

static void one_exit(void)
{
        printk("module one leaving the semaphore\n");
        leave_sem();
}

module_init(one_init);
module_exit(one_exit);

MODULE_LICENSE("GPL");
