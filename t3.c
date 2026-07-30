// 信号量
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
//信号量
#include <semaphore.h>

sem_t sem;

int count = 0;

void *task(void *p)
{
    for (int i = 0; i < 100000; i++)
    {
        // 若信号量值为0，则阻塞等待，直到信号量值大于0，线程执行，-1
        sem_wait(&sem);
        count++;
        // +1，唤醒一个等待该信号量的线程
        sem_post(&sem);
    }
    // return NULL;
}

int main(int argc, char const *argv[])
{
    // 2.是否进程间共享 ；0 一个进程内多个进程间；1 多个进程间
    // 3.初始值
    sem_init(&sem, 0, 1);
    
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, (void *)sem_wait, &sem);
    pthread_create(&t2, NULL, (void *)sem_wait, &sem);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("count = %d\n", count);
    sem_destroy(&sem);
    return 0;
}
