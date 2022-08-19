//通过结构体传递多个参数。可以在线程回调中传递任意的数据类型，因为它指向 void
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5      //线程个数

struct thread_data{
    int thread_id;
    double message;
};

void *print_hello(void *threadarg)
{
    struct thread_data *my_data =  (struct thread_data *) threadarg;

    printf("Thread ID : %d\n", my_data->thread_id);
    printf("Message : %f\n", my_data->message);

    pthread_exit(NULL);
}

int main()
{
    //定义线程的 id 变量，多个变量使用数组
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        printf("main() : creating thread, %d\n", i);
        td[i].thread_id = i;
        td[i].message = i;
        int ret = pthread_create(&threads[i], NULL, print_hello, (void*)&(td[i]));
        if (ret != 0) {
            printf("pthread_create error: error_code = %d\n", ret);
            exit(-1);
        }
    }

    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}
