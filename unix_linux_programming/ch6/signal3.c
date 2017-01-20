/*
 *     File Name: signal3.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月20日 星期五 03时31分27秒
 *
 *      这个程序的意思是捕捉自己定义的信号，可以利用
 *		kill -USR1	xx
 *	这个xx就是下面这个程序的	ps  -a
 *	会接受到这个信号
 */
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo)
{
	if (signo == SIGUSR1)
		printf("received SIGUSER1\n");
	else if (signo == SIGKILL)
		printf("received SIGKILL\n");
	else if (signo == SIGSTOP)
		printf("received SIGSTOP\n");
}
int main()
{
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGUSR1\n");
	if (signal(SIGKILL, sig_handler) == SIG_ERR)
		printf("\ncan't  catch SIGKILL\n");
	if (signal(SIGSTOP, sig_handler) == SIG_ERR)
		printf("\ncan't  catch SIGSTOP\n");
	while(1)
		sleep(1);
	return 0;
}
