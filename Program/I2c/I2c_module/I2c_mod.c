/********************LCD interfacing via I2c*********************************/

#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define I2C_ADDR 0x27

//static struct i2c_adapter *i2c_module;  //added for getting i2c Bus
static struct class *cl;// Global variable for the device class
static dev_t dev_num;
static struct i2c_client *client;
static struct cdev led_cdev;




static int lcd_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int lcd_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t lcd_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    char buffer[count+1];

    if (count > 16)
        return -EINVAL;

    if (copy_from_user(buffer, buf, count))
        return -EFAULT;

    buffer[count] = '\0';

    i2c_smbus_write_byte_data(client, 0x00, 0x01); // Clear display
    i2c_smbus_write_byte_data(client, 0x00, 0x80); // Set cursor to first line
    i2c_smbus_write_i2c_block_data(client, 0x40, count, buffer); // Write data to LCD

    return count;
}

static const struct file_operations lcd_fops = {
    .owner          = THIS_MODULE,
    .write          = lcd_write,
    .open           = lcd_open,
    .release        = lcd_release,
};

static int lcd_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    pr_info("LCD driver initialized\n");

    i2c_smbus_write_byte_data(client, 0x00, 0x38); // Initialize LCD, 2 lines, 5x8 dots
    i2c_smbus_write_byte_data(client, 0x00, 0x0C); // Display on, cursor off, blinking off
    i2c_smbus_write_byte_data(client, 0x00, 0x06); // Entry mode set, cursor increment

    return 0;
}

static int lcd_remove(struct i2c_client *client)
{
    pr_info("LCD driver removed\n");
    return 0;
}

static const struct i2c_device_id lcd_id[] = {
    { "lcd", 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, lcd_id);

static struct i2c_driver lcd_driver = {
    .driver = {
        .name   = "lcd",
        .owner  = THIS_MODULE,
    },
    .probe          = lcd_probe,
    .remove         = lcd_remove,
    .id_table       = lcd_id,
};

static int __init lcd_init(void)
{
    int ret;
    struct device *dev_ret;

    ret = i2c_add_driver(&lcd_driver);
    if (ret < 0) {
        pr_err("Failed to register LCD driver: %d\n", ret);
        return ret;
    }
    
    cl = class_create(THIS_MODULE, "LCD_MODULE");//This one is create a node in dev file
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev_num, NULL, "I2C_LCD"))) // inside Lcd_module node I2c_LCD module is created 
    {
        class_destroy(cl);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(dev_ret);
    }

    pr_info("LCD driver loaded\n");
    return 0;
}

static void __exit lcd_exit(void)
{

	
    i2c_del_driver(&lcd_driver);
    pr_info("LCD driver unloaded\n");
    device_destroy(cl, dev_num); //Module destroy first
    class_destroy(cl);// Node is Destroy then
    // Remove the character device from the kernel
    cdev_del(&led_cdev);
}

module_init(lcd_init);
module_exit(lcd_exit);

MODULE_AUTHOR("Mandar");
MODULE_DESCRIPTION("LCD Driver");
MODULE_LICENSE("GPL");

