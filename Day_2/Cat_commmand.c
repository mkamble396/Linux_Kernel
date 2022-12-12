// WAP our own version of cat command using mmap system call
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/stat.h>
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage:./a.out Filename\n");
        return 0;
    }
    int fd;
    char * region;
    struct stat s;
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        printf(" file is Not present\n");
        return -1;
    }

    fstat(fd,&s);
    region = mmap(0,1,PROT_READ,MAP_SHARED,fd, 0);
    for(int i = 0;i<s.st_size;i++)
    {
        printf("%c",region[i]);
    }
    close(fd);
    return 0;
}
