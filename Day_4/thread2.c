#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);
int run_now = 1,n;
char message[] = "Hello World";

int main() 
  {
    int res;
    pthread_t a_thread;
    void *thread_result;
    int print_count1 = 0;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0) 
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    while(print_count1++ < 20) 
     {
        if (run_now == 2) 
        {  
          if(print_count1 % 2==0)
          printf("%d\n",print_count1);
          run_now = 1;
        }
        else
        {
            sleep(1);
        }
    }
  //while(1)
  //  printf("1");

    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) 
{
    int print_count2 = 0;

    while(print_count2++ < 20)
    {
        if (run_now == 1)
         { 
            if(print_count2 % 2 !=0)
            printf("%d\n",print_count2);
            run_now = 2;
         }
        else 
         {
            sleep(1);
         }
    }
    while(1)
	pthread_exit("Thank you for the cpu time");
}
