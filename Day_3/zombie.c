// program for Zombie process
#include<stdio.h>
#include<unistd.h>
int main()
{
        if(fork()==0)
        {
                printf("in child pid=%d ppid=%d\n",getpid(),getppid());
                sleep(10);
                printf("child is terminating\n");
        }
        else
        {
                printf("in parent pid=%d ppid=%d\n",getpid(),getppid());
                while(1);
        }
}
