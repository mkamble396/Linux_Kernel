
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/module.h>

int id;
int count = 0;

irqreturn_t keyboard_handler(int irq, void *id)
{
	printk("Inside the handler\n");

	count++;
	printk(" The count is %d \n", count );

	return IRQ_HANDLED;

}
int init_module(void)
{
	int rv;
	printk("Module for interrupt handler is loaded\n");
	
	//Int request_ irq (unsigned int irq, Irq_handler _t(*handler)(int,void*),Unsigned long irqflags , Const char *dev_name , Void*dev_id);
	rv = request_irq(1, keyboard_handler, IRQF_SHARED, "kernel_manish", &id); // this is interrupt resgistration inside that irq= its a interrupt number 
	// interrupt calling fucntion  , flags 
	
	printk("rv : %d\n",rv);

	if (rv < 0)
	{
		printk(" can't get interupt 51\n");
	}
	return 0;
}

void cleanup_module(void){
	printk("Module for interrupt handler is unloaded\n");
	free_irq(1, &id);
}

MODULE_AUTHOR (" MANISH  ");
MODULE_DESCRIPTION(" INTRUPT HANDLER MODULE FOR KEYBOARD  ");
MODULE_LICENSE("GPL");
