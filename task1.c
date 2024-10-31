#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* child_thread(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    srand(time(NULL));
    pthread_create(&thread, NULL, child_thread, NULL);

    for (int i = 1; i <= 10; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }

    pthread_join(thread, NULL);
    return 0;
}
