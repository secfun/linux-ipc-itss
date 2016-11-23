//
// Created by xdy on 16/11/23.
//

#include "stdio.h"
#include "pthread.h"

void print_zero(void) {
    while (1) {
        puts("00000000000000");
    }
}

void print_one(void) {
    while (1) {
        puts("11111111111111");
    }
}

int main() {
    puts("start");
    pthread_t pthread_t0, pthread_t1;

    pthread_create(&pthread_t0, NULL, (void *) print_zero, NULL);
    pthread_create(&pthread_t1, NULL, (void *) print_one, NULL);

    pthread_join(pthread_t0, NULL);
    pthread_join(pthread_t1, NULL);
    puts("end");
    return 0;
}