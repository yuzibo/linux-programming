/*
 *     File Name: thread_1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2018年05月17日 星期四 10时21分54秒
 *     usage: gcc thread_1.c -lpthread -o test
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <pthread.h>
#define NUM_THREADS 5
/*
 *
 *进程— 资源分配的最小单位
 线程— 程序执行的最小单位
 */
/**
 * 这个小程序对于c  的指针的要求挺高的
 *
 */
void *say_hello(void *threadid)
{
	int tid = *((int*)threadid);
	printf("Hello yubo! Thread ID = %d\n", tid);
	pthread_exit(NULL);
}
int main()
{
	pthread_t threads[NUM_THREADS];
	int index[NUM_THREADS];
	int i;
	for (i = 0; i < NUM_THREADS; i++)
	{
		printf("main() : create thread, %d\n",i);
		index[i] = i;
		int ret = pthread_create(&threads[i], NULL, say_hello, (void*)&(index[i]));
		if (ret != 0)
		{
			printf("pthread_create error: error_code = %d\n", ret);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
