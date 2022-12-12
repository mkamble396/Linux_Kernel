#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* routine() {
    printf("Hello from threads\n");
   // sleep(2);
    printf("Ending thread\n");
}

int main() {
    pthread_t p1, p2;
    if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    sleep(5);
   // if (pthread_join(p1, NULL) != 0) {
      //  return 3;
   //}
    return 0;
}

