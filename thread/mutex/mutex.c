//
// Created by xdy on 16/11/23.
//
#include "stdio.h"
#include "pthread.h"
#include "time.h"

int shared_int;
pthread_mutex_t mutex_t;


void increase(void) {
    printf("current thread id: %d,init shared_int: %d\n",pthread_self(), shared_int);
    pthread_mutex_lock(&mutex_t);
    printf("current thread id: %d,start shared_int: %d\n",pthread_self(), shared_int);
    for (int i = 0; i < 100000; ++i) {
        shared_int += 1;
    }
    printf("end shared_int: %d\n", shared_int);
    pthread_mutex_unlock(&mutex_t);
}

int main() {
    pthread_mutex_init(&mutex_t, NULL);
    pthread_t pthread_t1, pthread_t2, pthread_t3;
    pthread_create(&pthread_t1, NULL, (void *) increase, NULL);
    pthread_create(&pthread_t2, NULL, (void *) increase, NULL);
    pthread_create(&pthread_t3, NULL, (void *) increase, NULL);

    pthread_join(pthread_t1, NULL);
    pthread_join(pthread_t2, NULL);
    pthread_join(pthread_t3, NULL);
    printf("shared_int: %d", shared_int);
    return 0;
}

/*output
/Users/xdy/Library/Caches/CLion2016.1/cmake/generated/algo-6e4e421/6e4e421/Debug0/algo
current thread id: 528384,init shared_int: 0
current thread id: 1064960,init shared_int: 0
current thread id: 1601536,init shared_int: 0
current thread id: 528384,start shared_int: 0
end shared_int: 100000
current thread id: 1064960,start shared_int: 100000
end shared_int: 200000
current thread id: 1601536,start shared_int: 200000
end shared_int: 300000
shared_int: 300000
Process finished with exit code 0
 * */

/*
 通过结果可以看出来线程的内部的代码可以被"原子性"的执行,最后的结果也变成了预期的300000.

 另外还有两个函数:
 int pthread_mutex_trylock(pthread_mutex_t *);
 这个函数在加锁失败时不会会让线程进入睡眠状态，它直接失败返回，所以需要自己判断返回值。

 int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex,
                             const struct timespec *restrict tsptr);
 使用这个函数可以指定一个超时时间，在这个超时时间到来之前如果没有获得锁，则失败返回，不会一直阻塞.注意这个时间不是时间段,而是一个阻塞到时间点的时间戳.

 释放资源
 pthread_mutex_destroy(pthread_mutex_t *mutex);
 如果在初始化互斥量的时候，分配了其它资源，需要使用上面这个函数来释放掉这些资源。这个函数执行之后，互斥量变成了未初始化的状态，对它执行操作的结果是未定义的。如果需要再次使用这个互斥量的话，可以再次执行初始化函数来初始化。
 * */