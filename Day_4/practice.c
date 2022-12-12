// Practice purpose create a thread and join

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void* routine()
{
    printf("Hello from thread\n");
//   sleep(3);
    printf("Ending  Thread\n");

}

int main(int c, char *v[])
   {
       pthread_t p1;
        
       pthread_create(&p1,NULL,&routine,NULL);
      // pthread_exit(NULL);
       pthread_join(p1,NULL);

   }
