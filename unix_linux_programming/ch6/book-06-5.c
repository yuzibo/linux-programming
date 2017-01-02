/*
 *     File Name: book-06-5.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月01日 星期日 01时24分49秒
 *     忽略信号的程序
 */
#include<stdio.h>
#include<signal.h>
int main()
{
	signal(SIGINT, SIG_IGN);
	printf("you can't stop me\n");
	while(1){
		sleep(1);
		printf("haha\n");
	}
}
