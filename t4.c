// 信号量
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
//信号量
#include <semaphore.h>
// 最大负载
#define MAX 4
// 线程数量
#define NUM 16
sem_t sem;

int count = 0;

void *task(void *p)
{
    
    int id = *((int *)p);
    free(p);
    printf("线程%d尝试进入临界区\n", id);
}

int main(int argc, char const *argv[])
{
    // 2.是否进程间共享 ；0 一个进程内多个进程间；1 多个进程间
    // 3.初始值
    sem_init(&sem, 0, MAX);
    
    pthread_t tid[NUM];
    for (int i = 0; i < NUM; i++)
    {
        // 动态分配内存，避免线程共享同一个变量
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&tid[i], NULL, task, id);
    }
    for (int i = 0; i < NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
    printf("count = %d\n", count);
    
    sem_destroy(&sem);
    return 0;
}
