/*
 *     File Name: book-070404.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月03日 星期二 08时57分13秒
 */
#include<stdio.h>
#include<signal.h>

void wakeup(int);

int main()
{
	printf("about to sleep for 4 seconds\n");
	signal(SIGALRM, wakeup);
	alarm(4);
	pause();
	printf("morning so soon?\n");
}
void wakeup(int signum)
{
#ifndef	SHHHH
	printf("Alarm received from kernel\n");
#endif
}
