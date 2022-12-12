//Write a program to read framebuffer fixed size information? Hint: Device name is /dev/fb0.
#include<stdio.h>
#include<fcntl.h>
#include<linux/input.h>
#include<sys/ioctl.h>
#include<linux/fb.h>
int main(int c, char *v[])
{
	int fd1;
	
	fd1 = open (v[1], O_RDONLY);
	if(fd1 < 3)
	{
		printf("Usage:sudo ./a.out /dev/fb0\n");
		return 0;
	}

	struct fb_var_screeninfo varInfo;
       	
	ioctl(fd1, FBIOGET_VSCREENINFO,&varInfo);
	
	printf("visiable res-%u\nvisiable res-%u\nvirtual res-%u\nvirtual res-%u\nbits per pixel-%u\n", varInfo.xres,varInfo.yres,varInfo.xres,varInfo.yres,varInfo.bits_per_pixel);
	
	
	return 0;
}


