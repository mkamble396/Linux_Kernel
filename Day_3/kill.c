#include<error.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
 if(argc!=3)
  {
   // printf("error=%d\n",errno);
    perror("fail\n");
  }
 kill(atoi(argv[2]),atoi(argv[1]));
}


