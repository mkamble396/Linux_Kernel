//*************MMAP exmple*******************//

#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int c, char *argv[])
{
    char *addr, *starting_addr;
    int fd;
    fd=(argv[1],O_RDONLY);
    if(fd==-1)
        return 0;
   starting_addr=mmap(0,100,PROT_READ,MAP_PRIVATE,fd,0);// *mmap(void *address,size_t length,int prot,int flags,int fd, off_t set(NULL))
        printf("%p\n",starting_addr);

}


