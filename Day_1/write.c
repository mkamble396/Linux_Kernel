#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(int c, char*v[])
{
    int f1,count,f2;
    f1=open(v[1],O_RDWR);

    char buff[100];
       lseek(f1,0,SEEK_END); 
        read(0,buff,10);
    count=write(f1,buff,10);
    buff[count]='\0';

}
