#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void *producer(void *arg);
void *consumer(void *arg);
int counter =0;
char buffer[5];
int main(){
	int res;
	pthread_t a_thread,b_thread;
	void *thread_result;

	if((pthread_create(&a_thread,NULL,producer,NULL)) != 0)
	{
		perror("thread_1 creation failed");
		exit(EXIT_FAILURE);
	}

	if((pthread_create(&b_thread,NULL,consumer,NULL)) != 0)
	{
		perror("thread_2 creation failed");
		exit(EXIT_FAILURE);
	}
	printf("wait for pthread_join\n");
	if(pthread_join(a_thread,NULL)!=0)
	{
		perror("thread join failed");
		exit(EXIT_FAILURE);
	}
	if(pthread_join(b_thread, NULL)!=0)
	{
		perror("thread join failed\n");
		exit(EXIT_FAILURE);
	}
	printf("thread joined\n");
	exit(EXIT_SUCCESS);
}

void *producer(void *arg){
	int i=0;
	char ch='A';
	while(1)
	{
		while(counter ==5);
		buffer[i]=ch;
		i = (i+1)%5;
		sleep(0.5);

		if(i ==0)
		{
			ch='A';
			printf("p:%s\n",buffer);
		}
		else
		{
			ch++;
		}
		counter++;
		
	}
	pthread_exit("exit");

}
void* consumer(void *arg){
	int out=0;
	char data[5];
	while(1)
	{
		while(counter ==0);
		data[out]=buffer[out];
		out = (out+1)%5;
		sleep(0.5);
		if(out == 0)
			printf("\t:c:%s\n",data);
		counter--;

	}
	pthread_exit("exit");
}

