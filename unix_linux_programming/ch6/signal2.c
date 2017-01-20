/*
 *     File Name: signal.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月20日 星期五 03时13分51秒
 *     这个函数是在一个死循环中捕捉   SIGINT 这个信号
 */
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo)
{
	if (signo == SIGINT)
		printf("received SIGINT\n");
}
int main()
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGINT\n");
	while(1)
		sleep(1);
	return 0;
}
