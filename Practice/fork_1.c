// Try fork system as per codevault video

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int c,char*v[])
{
    int n;
    int id=fork();

    //    printf("Hello from id=%d\n",id);
    if(id==0)
    {
        n=1;
    } 
    else {
        n=6;
    }

    if(id!=0)
    {
        wait(NULL);
    }
    int i;
    for(i=n;i<n+5;i++)
    {
        printf("i=%d ",i);
        fflush(stdout);

    }
    printf("\n");
}
