/*
 *     File Name: exec1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年05月18日 星期四 06时36分59秒
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *arglist[3];

	arglist[0] = "ls";
	arglist[1] = "-l";
	arglist[2] = 0;
	printf("***中断这个程序的执行***\n");
	execvp(arglist[0], arglist);
	printf("ls is done, bye\n");
}

