/*
 *     File Name: echostate.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月15日 星期五 03时40分10秒
 */
#include<stdio.h>
#include<termios.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	struct termios	info;
	int recv;
	/* read value from driver */

	recv = tcgetattr(0, &info);
	if (recv == -1){
		perror("tcgetattr");
		exit(1);
	}
	if (info.c_lflag & ECHO)
		printf(" echo is on,since its bit is 1\n");
	else
		printf("echo is off, since its bit is 0\n");
}
