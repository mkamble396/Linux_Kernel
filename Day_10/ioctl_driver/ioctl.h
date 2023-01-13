#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>

#define MAGIC_NUMBER 'O'

#define SET_BAUD_RATE  _IOWR(MAGIC_NUMBER, 8, int)
#define SET_NO_STOP_BITS _IOWR(MAGIC_NUMBER, 9, int)
#define SET_DIRECTION_WRITE _IOW (MAGIC_NUMBER, 10, int)
