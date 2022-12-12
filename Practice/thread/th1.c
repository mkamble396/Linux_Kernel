// thread creation and  thread synchronization
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int id=0;
int i=0;
pthread_mutex_t mtx;

void* routine()
{
    pthread_mutex_lock(&mtx);
    for(i;i<1000000;i++,id++);
    printf("id=%d\n",id);
    pthread_mutex_unlock(&mtx);

}

int main(int c, char*v[])
{       int retval;

    pthread_t t1,t2,t3;

    if  ((pthread_create(&t1,NULL,&routine,NULL))!=0)
        return 1;

    if((pthread_create(&t2,NULL,&routine,NULL))!=0)
        return 2;


    if((pthread_create(&t3,NULL,&routine,NULL))!=0)
        return 3;

    //    pthread_detach(pthread_self());

    if(pthread_join(t1,NULL)!=0)
        perror("Exit Fail\n");

    pthread_join(t2,NULL);

    pthread_join(t3,NULL);
    return 0;
}
