#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"ioctl.h"

int main()
{
	int FileDesc, Result, BAUD_RATE = 9600, STP_BITS = 8;
	FileDesc=open("/dev/my_device",O_RDWR);

	if(FileDesc <0)
	{
		printf("\nError Opening Device\n");
		exit(1);
	}
	Result = ioctl (FileDesc, SET_BAUD_RATE, BAUD_RATE);
	if (Result < 0) {
		printf ("\n IOCTL Error");
		return (-1);
	}
	ioctl (FileDesc, SET_NO_STOP_BITS, STP_BITS);
	ioctl (FileDesc, SET_DIRECTION_WRITE, NULL);

	close(FileDesc);
}
