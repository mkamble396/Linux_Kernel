//Implementation of own kill Command 
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
int Kill(pid,signalnumber);
int main(int argc,char**argv)
{

    if(argc!=3)
    {
        printf("Usage: ./Mykill signal Number\n");
            return 0;
    }
        Kill(atoi(argv[1]),atoi(argv[2]));
                perror("KILL");


}
