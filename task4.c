#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* calculate_catalan(void* arg) {
    int n = *(int*)arg;
    int* catalan = malloc(n * sizeof(int));
    catalan[0] = 1;
    for (int i = 1; i < n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - 1 - j];
        }
    }
    return (void*)catalan;
}

void* calculate_primes(void* arg) {
    int n = *(int*)arg;
    int* primes = malloc(n * sizeof(int));
    int count = 0, num = 2;
    while (count < n) {
        int is_prime = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) primes[count++] = num;
        num++;
    }
    return (void*)primes;
}

int main() {
    pthread_t thread1, thread2;
    int n = 10;

    pthread_create(&thread1, NULL, calculate_catalan, &n);
    pthread_create(&thread2, NULL, calculate_primes, &n);

    int* catalan;
    int* primes;
    pthread_join(thread1, (void**)&catalan);
    pthread_join(thread2, (void**)&primes);

    printf("Catalan numbers: ");
    for (int i = 0; i < n; i++) printf("%d ", catalan[i]);
    printf("\n");

    printf("Prime numbers: ");
    for (int i = 0; i < n; i++) printf("%d ", primes[i]);
    printf("\n");

    free(catalan);
    free(primes);
    return 0;
}
