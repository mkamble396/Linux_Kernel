/*---------------------I2c_Module ---------------------
Icd-HD44780 operate through PCF 8574T I2c module using BBB board.

*/
#include<linux/module.h>  

#include<linux/init.h>

#include<linux/device.h>

#include<linux/fs.h>

#include<linux/i2c.h>

#include<linux/delay.h>

#include<linux/uaccess.h>

#include<linux/cdev.h>

#include<linux/slab.h>

#include<linux/gpio.h>



//------------------macros for programm----------------------
#define LCD_SLAVE_ADDR 0x27   //I2c address
#define SLAVE_DEVICE_NAME "LCD_DISPLAY"
#define I2C_BUS_AVAILABLE 2
#define ENABLE 0X04
#define RS 0x01
#define RW 0x00

#define PIN_SET 1
#define PIN_RESET 0

#define I2C_DELAY usleep_range(5, 10) 



//////Variable Declaration///////////////////
static struct i2c_adapter *LCD_I2C_adapter 	=NULL; //Adapter Structure
static struct i2c_client  *LCD_I2C_client	=NULL; //I2c client 
static struct class *cl;
static dev_t dev_lcd_num;// for Getting major and minior number( vendor id) 
static struct cdev lcd_cdev;



//////////--------------Function Declaration----------------------////////

static int LCD_I2C_probe(struct i2c_client *LCD_I2C_Client,const struct i2c_device_id *id); //This function getting called when the slave has been found
static int LCD_I2C_remove(struct i2c_client*);
static ssize_t lcd_write(struct file *filp, const char __user *buf, size_t count, loff_t *pos);
static ssize_t lcd_read(struct file *filp, char __user *buf, size_t count, loff_t *pos);
static int lcd_open(struct inode *inode, struct file *filp);
static int lcd_release(struct inode *inode, struct file *filp);



/////////////--------Structure Declaration------------///////////
/*Structure that has slave device Id*/

static const struct i2c_device_id LCD_I2C_id[] ={
	{SLAVE_DEVICE_NAME,0},
	{}
};
MODULE_DEVICE_TABLE(i2c,LCD_I2C_id);


static struct i2c_driver LCD_I2C={
.driver = {
	.name	= SLAVE_DEVICE_NAME,
	.owner	= THIS_MODULE,
	},
	.probe		= LCD_I2C_probe,
	.remove 	= LCD_I2C_remove,
	.id_table	= LCD_I2C_id,


};


static const struct file_operations lcd_fops = {
    .owner = THIS_MODULE,
    .read = lcd_read, 
    .write = lcd_write,
   .open = lcd_open,
    .release = lcd_release,
};


static struct i2c_board_info lcd_i2c_board_info =
{
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME ,LCD_SLAVE_ADDR)
};

//////////////------------ Function definitions----------------///////////
static int LCD_I2C_probe(struct i2c_client *LCD_I2C_Client,const struct i2c_device_id *id)
{
	printk(KERN_INFO"Probe Function Invoked\n");
	return 0;
}


static int LCD_I2C_remove(struct i2c_client *LCD_I2C_Client)
{
	printk(KERN_INFO"LCD driver removed");
	return 0;
}



// Function to handle device file open events
static int led_open(struct inode *inode, struct file *filp)
{
    return 0;
}

// Function to handle device file close events
static int led_release(struct inode *inode, struct file *filp)
{
    return 0;
}


// Function to turn the LED on or off
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
	printk(KERN_INFO"LCD write");
	return 0;
	
   
}

static ssize_t led_read(struct file *filp,  char __user *buf, size_t count, loff_t *pos)
{
	 printk(KERN_INFO"LCD driver Read");
	return 0;

}




//*-------------Initialization-----------------------*
static int __init LCD_I2C_init(void)
{

int err,ret_driver;

	/*-----------------------------------------gpio module---------------------------------*/
    
    struct device *dev_ret; //checking device is created properly or not 
    // Allocate a character device number
    err = alloc_chrdev_region(&dev_lcd_num, 0, 1, "LCD");
    if (err < 0) {
        printk(KERN_ERR "LCD: failed to allocate device number\n");
        return err;
    }

   // Initialize the character device
    cdev_init(&lcd_cdev, &lcd_fops);
    lcd_cdev.owner = THIS_MODULE;
 

    // Add the character device to the kernel
    err = cdev_add(&lcd_cdev, dev_lcd_num, 1);
    if (err < 0) {
        printk(KERN_ERR "LCD: failed to add character device\n");
        unregister_chrdev_region(dev_lcd_num, 1);
        return err;
    }

    // Character Device Files - Creation & Operations

    cl = class_create(THIS_MODULE, "LCD_I2C_MODULE");//This one is create a node in dev file
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev_lcd_num, NULL, "LCD_I2C_Module"))) // inside LED_MODULE node GPIO_LED module is created 
    {
    	printk(KERN_ERR"LCD: Module is not created ");
        class_destroy(cl);
        unregister_chrdev_region(dev_lcd_num, 1);
        return PTR_ERR(dev_ret);
    }


    // Request the GPIO pin
    err = gpio_request(LCD_SLAVE_ADDR , "LCD_I2C");
    if (err < 0) {
        printk(KERN_ERR "LCD: failed to request I2c pin\n");
        cdev_del(&lcd_cdev);
        unregister_chrdev_region(dev_lcd_num, 1);
        return err;
    }

	LCD_I2C_adapter  = i2c_get_adapter(I2C_BUS_AVAILABLE);
    if (!LCD_I2C_adapter) {
        pr_err("Could not get I2C adapter\n");
        return -1;
    }
    else
    LCD_I2C_client=i2c_new_device(LCD_I2C_adapter,&lcd_i2c_board_info);
    
     ret_driver = i2c_add_driver(&LCD_I2C);
    if (ret_driver < 0) {
        pr_err("Failed to register LCD driver: %d\n", ret_driver);
        return ret_driver;
    }
    
   


    // Set the direction of the GPIO pin to output
//    gpio_direction_output(LED_GPI, 0);
 printk(KERN_INFO "LCD: device driver initialized\n");
    return 0;

}


//*--------Exit-----------------*
static void __exit LCD_I2C_exit(void)
{
    // Free the I2C client structure and adapter
    kfree(LCD_I2C_client);
    i2c_put_adapter(LCD_I2C_adapter);
    
    // Release the character device number
    unregister_chrdev_region(dev_lcd_num, 1);
	
// Deleting  I2c driver 
    i2c_del_driver(& LCD_I2C);
    pr_info("I2C device Deleted\n");
    //device destroy 
    device_destroy(cl, dev_lcd_num); //Module destroy first
    class_destroy(cl);// Node is Destroy then
    
    // Remove the character device from the kernel
    cdev_del(&lcd_cdev);
    printk(KERN_INFO "LCD_Module: device driver cleaned up\n");
}


//**********************Module***********************
module_init(LCD_I2C_init);
module_exit(LCD_I2C_exit);

MODULE_AUTHOR("Mandar");
MODULE_DESCRIPTION("LCD_I2c_Driver");
MODULE_LICENSE("GPL");








