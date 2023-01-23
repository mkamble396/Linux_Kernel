//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 8


pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;

void* producer(void* args) {
    // Produce
    int x = rand() % 100;

    // Add to the buffer
    if(count<10)
    {
        pthread_mutex_lock(&mutexBuffer);
        buffer[count] = x;
        count++;
        pthread_mutex_unlock(&mutexBuffer);
    }
}

void* consumer(void* args) {
    int y;

    // Remove from the buffer
    pthread_mutex_lock(&mutexBuffer);
    y = buffer[count - 1];
    count--;
    pthread_mutex_unlock(&mutexBuffer);

    // Consume
    printf("Got %d\n", y);
    sleep(1);
}


int main(int argc, char* argv[]) {
    srand(time(NULL)); //function sets its argument as the seed for a  new  sequence  of  pseudo-random  integers  to be returned by rand(). 
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (i > 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}
