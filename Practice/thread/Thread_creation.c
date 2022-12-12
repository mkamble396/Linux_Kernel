// thread creation and 
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

    int i=0;
void* routine()
{
    int id;
    printf("Hello from Routine id=%d\n",getpid());


}

int main(int c, char*v[])
{
    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,&routine,NULL);
    pthread_create(&t2,NULL,&routine,NULL);
    pthread_create(&t3,NULL,&routine,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}
