// program for even and odd sum using mutex
// create execute file using "gcc filename.c -o Exe_filename -phthread"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> /// therad opreation



int min,max,i,ev_sum, odd_sum;  // global variable
pthread_mutex_t mutex;



void* sum() {
        pthread_mutex_lock(&mutex);
        for (; i <=max; i++) {
                if(i % 2==0)
                        ev_sum = ev_sum + i;
                if(i %2 ==1)
                        odd_sum = odd_sum + i;
        }
        pthread_mutex_unlock(&mutex);
}



int main(int argc, char* argv[])
{
        pthread_t p1, p2;
        printf("ENter any range min and max\n");
        scanf("%d%d", &min, &max);
        i = min;
        pthread_mutex_init(&mutex, NULL); //mutex opreation
        if (pthread_create(&p1, NULL, &sum, NULL) != 0) {
                return 1;
        } //created thread p1 and passes the null argu and catching  null argu 
        if (pthread_create(&p2, NULL, &sum, NULL) != 0) {
                return 2;
        }
        if (pthread_join(p1, NULL) != 0) {
                return 5;
        } //join for wait until p1 thread complete the task 
        if (pthread_join(p2, NULL) != 0) {
                return 6;
        }// join for wait until p2 thread complete the task
        pthread_mutex_destroy(&mutex);//



       printf("even sum is %d\n", ev_sum);
        printf("odd sum is %d\n", odd_sum);
        return 0;
}
