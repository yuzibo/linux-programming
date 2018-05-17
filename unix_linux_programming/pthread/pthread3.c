/*
 *     File Name: pthread3.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2018年05月17日 星期四 11时28分49秒
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

struct thread_data{
	int thread_id;
	double message;
};

void *print_hello(void *threadarg)
{
	struct thread_data *my_data = (struct thread_data *)threadarg;
	printf("Thread ID: %d\n", my_data->thread_id);
	printf("Message : %f\n", my_data->message);
}
int main()
{
	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	int i;
	for(i = 0; i < NUM_THREADS; i++)
	{
		printf("main(): creating thread, %d\n", i);
		td[i].thread_id = i;
		td[i].message = i;
		int ret = pthread_create(&threads[i], NULL, print_hello, (void*)&(td[i]));
		if(ret != 0){
			printf("pthread_create error: error_code = %d\n", ret);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
