//WAP create two threads using pthreads and print even no and odd no alternatively.

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>


int min,max;
void* even()
{
    for (; min <= max;)
    {
        if(min % 2 == 0)
        {
            printf("e=%d\t",min);
            min++;
        }
    }
}





void* odd()
{
    for (; min <= max;)
    {
        if(min % 2 == 1)
        {
            printf("o=%d\t",min);
            min++;
        }
    }
}



int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    printf("enter min and max value: ");
    scanf("%d %d",&min, &max);
    if (pthread_create(&t1, NULL, &even, NULL) != 0)
    {
        return 1;
    }
    if (pthread_create(&t2, NULL, &odd, NULL) != 0)
    {
        return 2;
    }



   if (pthread_join(t1, NULL) != 0)
    {
        return 5;
    }
    if (pthread_join(t2, NULL) != 0)
    {
        return 6;
    }

        printf("\n");

   return 0;
}


