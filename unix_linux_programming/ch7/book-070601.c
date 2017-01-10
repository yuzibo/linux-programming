/*
 *     File Name: book-070601.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月04日 星期三 08时02分58秒
 */
#include<stdio.h>
#include<sys/time.h>
#include<signal.h>

/* 信号处理函数 */
/*
 *  也就是收到SIGALRM信号后执行的操作
 *
 */
void countdown(int signum)
{
	static int num = 10;
	printf("%d.. ", num--);
	fflush(stdout);
	if(num < 0){
		printf("DONE!\n");
		exit(0);
	}

}
/**
 * 以 毫秒(milliseconds)为参数，转化为整秒和微妙(microseconds)
 *
 */
int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs / 1000; /* 整数部分 */
	n_usecs = (n_msecs % 1000) * 1000L; /* 余数部分 */

	new_timeset.it_interval.tv_sec = n_sec; /* 设置重新加载 */
	new_timeset.it_interval.tv_usec = n_usecs; /* ？*/

	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs; /* 保存 计时值*/

	return setitimer(ITIMER_REAL, &new_timeset, NULL);

}



int main()
{

	signal(SIGALRM, countdown);
	if( set_ticker(500) == -1)
		perror("set_ticker");
	else while(1)
		pause();
	return 0;
}
