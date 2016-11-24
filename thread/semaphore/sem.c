//
// Created by xdy on 16/11/24.
//

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>


sem_t sem_t1;

char *get_time() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *now = asctime(timeinfo);
    return now;
}

void produce(void) {
    while (1) {
        sleep(1);
        sem_post(&sem_t1);
        printf("thread produce at %s\n", get_time());
    }
}

void consume(void) {
    while (1) {
        sleep(3);
        sem_wait(&sem_t1);
        printf("thread consume at %s\n", get_time());
    }
}

int main() {
    puts("semaphore");
    sem_init(&sem_t1, 0, 0);
    pthread_t pthread_t1, pthread_t2;
    pthread_create(&pthread_t1, NULL, (void *) produce, NULL);
    pthread_create(&pthread_t2, NULL, (void *) consume, NULL);

    pthread_join(pthread_t1, NULL);
    pthread_join(pthread_t2, NULL);
}

/*output
 xudy@iZ286wee5zoZ ~/tmp> ./sem
semaphore
thread produce at Fri Nov 25 00:05:50 2016

thread produce at Fri Nov 25 00:05:51 2016

thread consume at Fri Nov 25 00:05:52 2016

thread produce at Fri Nov 25 00:05:52 2016

thread produce at Fri Nov 25 00:05:53 2016

thread produce at Fri Nov 25 00:05:54 2016

thread consume at Fri Nov 25 00:05:55 2016

thread produce at Fri Nov 25 00:05:55 2016

thread produce at Fri Nov 25 00:05:56 2016

thread produce at Fri Nov 25 00:05:57 2016

thread consume at Fri Nov 25 00:05:58 2016
 */

/*
 * 上边是在我电脑上的运行结果, sem_post 其实是一个P操作, 可以让sem_t1加1.
 * sem_wait调用时候根据当前sem_t1的值不同有两种变现:
 *      当sem_t1>0时候, 直接sem_t1 -= 1, 然后接着向下执行;
 *      当sem_t1<=0时候, 阻塞当前线程, 直到sem_t1的值大于0, 然后开始执行.
 *      todo:// 当两个线程分别被阻塞时候, 是不是先被阻塞的那个先执行? 还是两个进入race condition?
 *      
 * */


