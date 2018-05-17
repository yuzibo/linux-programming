/*
 *     File Name: thread.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2018年05月17日 星期四 09时21分58秒
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

void *say_hello(void *args)
{
	printf("Hello, yubo\n");
}

int main()
{
	/* define thread id var,
	 * */
	pthread_t tids[NUM_THREADS];
	int i;
	for(i = 0; i < NUM_THREADS; i++){
		/*
		 * args is thread-id thread call functions-args
		 */
		int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
		if (ret != 0){
			printf("pthread_create error: error-code = %d\n",ret );
		}
	}
	pthread_exit(NULL);
}
