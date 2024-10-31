#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int target_number = 7;

void* print_thread(void* arg) {
    for (int i = 1; i <= 10; i++) {
        printf("Print Thread. Iteration: %d\n", i);
        sleep(1);
    }
    return NULL;
}

void* random_thread(void* arg) {
    int count = *(int*)arg;
    for (int i = 0; i < count; i++) {
        int rand_num = rand() % 10;
        printf("Random Thread generated: %d\n", rand_num);
        if (rand_num == target_number) {
            printf("Target number %d found, exiting.\n", target_number);
            pthread_exit(NULL);
        }
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t printThread, randomThread;
    srand(time(NULL));

    int rand_count = 10;
    pthread_create(&printThread, NULL, print_thread, NULL);
    pthread_create(&randomThread, NULL, random_thread, &rand_count);

    pthread_join(printThread, NULL);
    pthread_join(randomThread, NULL);

    printf("Main Thread: Both threads completed.\n");
    return 0;
}
