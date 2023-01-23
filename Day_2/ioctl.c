#include<stdio.h>
#include<fcntl.h>
#include<linux/input.h>
int main(int c, char **v)
{
    int fd;
   char name[256];
    fd=open(v[1],O_RDONLY);
    if(fd<3)
    {
        printf("Usage: sudo ./a.out /dev/input/event\n");
        return 0;
    }
    ioctl(fd,EVIOCGNAME(sizeof(name)),name);
    printf("Input Device Name:\"%s\"\n",name);
    return 0;
}
