//process practice program 
// create a process and terminate

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    fork();

    printf("Hello Mandar pid=%d ppid=%d\n",getpid(),getppid());
    fork();
    printf("Hi pid=%d ppid=%d\n",getpid(),getppid());
    exit(0);
}
