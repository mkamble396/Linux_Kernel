#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>
#include "export.h"

struct semaphore new;

static int get_sem(void)
{
        return down_interruptible(&new);  // Ctrl + c , Ctrl + z will works . Hence it can be used. 
//        printk("get_sem and the count is:%d\n",new.count);
//       down(&new);              // Ctrl + c, Ctrl + z will not works. Hence it cannot be used.   
//	return 0;

}
EXPORT_SYMBOL_GPL(get_sem);


static void leave_sem(void)
{
        up(&new);
        printk("leave_sem and the count is:%d\n",new.count);
}
EXPORT_SYMBOL_GPL(leave_sem);

static int export_init(void)
{
        sema_init(&new, 1);
        printk("semaphore new created and the count is:%d\n",new.count);
        return 0;
}

static void export_exit(void)
{
        printk("semaphore new removed\n");
}

module_init(export_init);
module_exit(export_exit);

MODULE_LICENSE("GPL");
