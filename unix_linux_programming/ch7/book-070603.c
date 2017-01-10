/*
 *     File Name: book-070603.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月07日 星期六 04时38分51秒
 */
/**
 * 使用例子来说明sigaction的调用
 * 好好体味这个程序，没有读懂
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int main()
{
	struct sigaction newact, oldact;

	/* 设置信号忽略 */
	newact.sa_handler = SIG_IGN; //这个地方也可以是函数
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	int count = 0;
	pid_t pid = 0;


	sigaction(SIGINT,&newact, &oldact);

	pid = fork();

	if(pid == 0){
		while(1){
			printf("I am child gaga...\n");
			sleep(1);
		}
		return 0;
	}
	while(1){
		if(count++ > 3){
			sigaction(SIGINT, &oldact, NULL); // 备份回来
			printf("pid = %d\n", pid);
			kill(pid, SIGKILL);


		}
		printf("I am father ...haha\n");
		sleep(1);
	}
	return 0;
}
