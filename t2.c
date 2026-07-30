// 自旋锁与互斥锁
#include <stdio.h>
#include <stdlib.h>
// POSIX(Linux\UNIX等系统接口规范) API
#include <pthread.h>
#define _POSIX_C_SOURCE 200809L

// 自旋锁
pthread_spinlock_t spin;
// 互斥锁
pthread_mutex_t mutex;

int c = 0;

void *task(void *p)
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&mutex);
        c++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    // 0 一个进程内多个进程间；1 多个进程间
    pthread_spin_init(&spin, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    pthread_create(&t1, NULL, task, NULL);
    pthread_create(&t2, NULL, task, NULL);
    pthread_create(&t3, NULL, task, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_spin_destroy(&spin);
    return 0;
}
