/*
 *     File Name: book-070604.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月07日 星期六 08时31分38秒
 */
#include<stdio.h>
#include<signal.h>

#define INPUTLEN	100

void inthandler(int s)
{
	printf("Called with signal %d\n", s);
	sleep(s);
	printf("done handing signal %d\n", s);
}
int main()
{
	struct	sigaction	newhandler; /* new settings */
	sigset_t	blocked; /* set of blocked sigs */
	char	x[INPUTLEN];
	/* load these two members first */
	newhandler.sa_handler = inthandler; /* 这里可以是其他函数 */
	newhandler.sa_flags = SA_RESETHAND | SA_RESTART; /* OPTIONS */
	/* then build the list of blocked signals */
	sigemptyset(&blocked); /* CLEAR all bits */
	sigaddset(&blocked, SIGQUIT); /* add SIGQUIT to list */
	newhandler.sa_mask = blocked; /* store blockmask */

	if(sigaction(SIGINT, &newhandler, NULL) == -1){
		perror("sigaction ");
	}
	else
		while(1){
			fgets(x, INPUTLEN, stdin);
			printf("input: %s", x);
		}


}
