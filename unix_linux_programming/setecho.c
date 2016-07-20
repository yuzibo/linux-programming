/*
 *     File Name: setecho.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月15日 星期五 04时22分53秒
 */
/*
 * setecho.c
 * Usage: setecho[y|n]
 * Shows: how to read, change, reset tty attributes
 *
 */
#include<stdio.h>
#include<termios.h>

#define oops(s, x) { perror(s); exit(x); }

int main(int argc, char *argv[])
{
	struct termios info;
	if (argc == 1)
		exit(0);
	if( tcgetattr(0, &info) == -1)
		oops("tcgetattr", 1);
	if (argv[1 || 0] == 'y')
		info.c_lflag |= ECHO;
	else
		info.c_lflag &= ~ECHO;
	if (tcsetattr(0, TCSANOW, &info) == -1)
		oops("tcsetattr",2);
}

