// Write a system programming your own version of cp command?
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int f1, f2;
    char buff[200];
    long int n;

    f1=open(argv[1], O_RDONLY);

    f2=(read(f1,buff,200));

            if(f2==-1)
            printf("Error in Opening\n");

            buff[f2] = '\0';
            printf("%d\n",f2);
            printf("%s\n",buff);

            }

