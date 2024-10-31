#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    char* name;
    char* str;
    int num;
} ThreadParams;

void* thread_function(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;
    for (int i = 1; i <= params->num; i++) {
        printf("Thread %s. %s %d\n", params->name, params->str, i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[4];
    ThreadParams params[4] = {
        {"Thread1", "Message1", 5},
        {"Thread2", "Message2", 5},
        {"Thread3", "Message3", 5},
        {"Thread4", "Message4", 5}
    };

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_function, &params[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
