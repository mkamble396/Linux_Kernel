// Fork() basic understanding 
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int m=0;
int main()
{

    int r,j,k;
    printf("Hello Before fork() pid=%d\tgetppid=%d\nm=%d\n",getpid(),getppid(),++m);
        wait(NULL);
       
    r=fork();
        ++m;
       // wait(NULL);
        printf("Hello after fork() pid=%d\tgetppid=%d\tr=%d\nvalue of m=%d\n",getpid(),getppid(),r,m);
       exit(0);
//   j=fork();
  //  printf("Hello after fork() pid=%d\tgetppid=%d\tj=%d\n",getpid(),getppid(),j);
//    exit(0);
}
