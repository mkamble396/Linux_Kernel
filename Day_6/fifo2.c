//job is read data from fifo and print it on screen
#include"header.h"
void main()
{
    mkfifo("f1",0664);
    perror("mkfifo");
    int fd = open("f1",O_RDONLY);
    if(fd < 0)
    {
        perror("open");
        return;
    }
    char s[20];
    read(fd,s,sizeof(s));
    printf("s=%s\n",s);
}
