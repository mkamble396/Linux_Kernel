//*********************I2c Char Module ******************************\\\\

#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

MODULE_LICENSE("GPL");

static struct i2c_adapter *i2c_module; 
static struct i2c_client *i2c_client;

static int __init i2c_init(void)
{
    int ret;

    // Get the I2C adapter corresponding to the BeagleBone Black board
    i2c_module = i2c_get_adapter(2);
    if (!i2c_adap) {
        pr_err("Could not get I2C adapter\n");
        return -1;
    }

    // Create a new I2C client structure for the target device
    i2c_client = kzalloc(sizeof(struct i2c_client), GFP_KERNEL);
    if (!i2c_client) {
        pr_err("Could not allocate memory for I2C client\n");
        ret = -ENOMEM;
        goto error_free_adapter;
    }

    // Set the I2C client address and adapter
    i2c_client->addr = 0x27;
    i2c_client->adapter = i2c_module;
    i2c_client->driver = &i2c_driver;

    /*/ Attach the I2C client to the I2C adapter
    ret = i2c_attach_client(i2c_client);
    if (ret < 0) {
        pr_err("Could not attach I2C client to adapter\n");
        goto error_free_client;
    }*/

    pr_info("I2C device attached\n");
    return 0;

/*/error_free_client:
   kfree(i2c_client);
error_free_adapter:
    i2c_put_adapter(i2c_adap);
*/
    return ret;
}

static void __exit i2c_exit(void)
{
    // Detach the I2C client from the adapter
    i2c_detach_client(i2c_client);

    // Free the I2C client structure and adapter
    kfree(i2c_client);
    i2c_put_adapter(i2c_adap);

    pr_info("I2C device detached\n");
}

module_init(i2c_init);
module_exit(i2c_exit);

