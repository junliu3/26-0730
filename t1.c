// 生产者消费者模型
#include <stdio.h>
#include <stdlib.h>

// POSIX(Linux\UNIX等系统接口规范) API
#include <pthread.h>
#include <unistd.h>
// 库存上限
#define MAX 5

// 互斥锁
pthread_mutex_t mutex;

// 条件变量与互斥锁配合使用
pthread_cond_t cond_full;
pthread_cond_t cond_empty;

// 产品数量
int store = 0;

void *producer(void *p)
{
    pthread_mutex_lock(&mutex);
    printf("生产者\n");
    for (int i = 0; i < 20; i++)
    {
        if (store == MAX)
        {
            printf("库存已满\n");
            // 释放CPU资源，进入阻塞状态，等待一个条件
            pthread_cond_wait(&cond_empty, &mutex);
        }
        // 生产
        store++;
        printf("生产：%d\n", store);
        // 唤醒一个等待该信号的进程
        // pthread_cond_signal(&cond_full);
        //
        pthread_cond_broadcast(&cond_full);
    }
    pthread_mutex_unlock(&mutex);
}
void *consumer(void *p)
{
    printf("消费者\n");
    for (int i = 0; i < 20; i++)
    {
        if (store == 0)
        {
            printf("库存为零，消费阻塞\n");

            pthread_cond_wait(&cond_full, &mutex);
        }
        //
        printf("消费：%d\n", store--);
        pthread_cond_signal(&cond_empty);
    }
    
}

int main(int argc, char const *argv[])
{
    // 初始化
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);
    pthread_t t_prod;
    pthread_t t_cons;
    // 线程函数，线程入口函数
    pthread_create(&t_prod, NULL, producer, NULL);
    pthread_create(&t_cons, NULL, consumer, NULL);
    // 等待子线程结束
    pthread_join(t_prod, NULL);
    pthread_join(t_cons, NULL);

    //销毁
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_full);
    pthread_cond_destroy(&cond_empty);

    return 0;
}
