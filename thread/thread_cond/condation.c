//
// Created by xdy on 16/11/23.
//
#include "stdio.h"
#include "pthread.h"
#include <unistd.h>

pthread_cond_t cond_t = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex_t;

void emit(void) {
    // sleep 3s
    for (int i = 0; i < 3; ++i) {
        printf("sleep %d s\n", i);
        sleep(1);
    }
    pthread_mutex_lock(&mutex_t);
    pthread_cond_signal(&cond_t);
    puts("emmit");
    pthread_mutex_unlock(&mutex_t);
}

void wait_signal(void) {
    pthread_cond_wait(&cond_t, &mutex_t);
    puts("emmited");
}

int main() {
    pthread_t emit_t, wait_signal_t;
    pthread_mutex_init(&mutex_t, NULL);

    pthread_create(&emit_t, NULL, (void *) emit, NULL);
    pthread_create(&wait_signal_t, NULL, (void *) wait_signal, NULL);

    pthread_join(emit_t, NULL);
    pthread_join(wait_signal_t, NULL);

    return 0;
}

/*output
 /Users/xdy/Library/Caches/CLion2016.1/cmake/generated/algo-6e4e421/6e4e421/Debug0/algo
sleep 0 s
sleep 1 s
sleep 2 s
emmit
emmited

Process finished with exit code 0

 * */

/*
 wait_emit直到emit触发过后才执行,线程的执行顺序得到保证.
 关于为什么需要lock,参考:http://stackoverflow.com/a/14925150/6877366

 * */