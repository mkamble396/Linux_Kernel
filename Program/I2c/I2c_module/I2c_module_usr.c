#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-2"
#define LCD_ADDRESS 0x27
#define LCD_COLS 16

int i2c_fd;

void lcd_init() {
    // send initialization commands to the LCD
    char buf[3] = {0x00, 0x38, 0x39};
    write(i2c_fd, buf, sizeof(buf));
    buf[1] = 0x14;
    buf[2] = 0x73;
    write(i2c_fd, buf, sizeof(buf));
    buf[1] = 0x56;
    buf[2] = 0x6c;
    write(i2c_fd, buf, sizeof(buf));
    usleep(10000);
    buf[1] = 0x38;
    buf[2] = 0x0c;
    write(i2c_fd, buf, sizeof(buf));
    buf[1] = 0x01;
    write(i2c_fd, buf, sizeof(buf));
    usleep(10000);
}

void lcd_send_cmd(int cmd) {
    // send a command to the LCD
    char buf[2] = {0x00, cmd};
    write(i2c_fd, buf, sizeof(buf));
}

void lcd_send_data(char *data) {
    // send data to the LCD
    int i;
    char buf[2];
    for (i = 0; i < LCD_COLS && data[i] != '\0'; i++) {
        buf[0] = 0x40;
        buf[1] = data[i];
        write(i2c_fd, buf, sizeof(buf));
    }
}

int main() {
    // open I2C bus
    i2c_fd = open(I2C_BUS, O_RDWR);
    if (i2c_fd < 0) {
        perror("Failed to open I2C bus");
        return 1;
    }

    // set I2C slave address
    if (ioctl(i2c_fd, I2C_SLAVE, LCD_ADDRESS) < 0) {
        perror("Failed to set I2C slave address");
        close(i2c_fd);
        return 1;
    }

    // initialize LCD
    lcd_init();

    // send a string to the LCD
    char *str = "Hello, world!";
    lcd_send_data(str);

    // close I2C bus
    close(i2c_fd);

    return 0;
}

