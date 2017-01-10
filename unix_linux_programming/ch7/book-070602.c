/*
 *     File Name: book-070602.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月04日 星期三 23时36分56秒
 */
/**
 *
 * 测试多个信号
 */
#include<stdio.h>
#include<signal.h>

#define INPUTLEN	100

void inthandler(int s)
{
	printf("Received signal %d .. waiting\n", s);
	sleep(2);
	printf("Leaving inthandler \n");

}

void quithandler(int s)
{
	printf("received signal %d ..waiting\n",s);
	sleep(3);
	printf("Leaving quithandler\n");
}
int main()
{
	char input[INPUTLEN];
	int nchars;

	signal(SIGINT, inthandler);
	signal(SIGQUIT, quithandler);

	do{
		printf("\n Type a message\n");
		nchars = read(0, input, (INPUTLEN - 1));
		if(nchars == -1)
			perror("read returned an error");
		else {
			input[nchars] = '\0';
			printf("You typed: %s", input);
		}
	}
	while(strncmp(input, "quit", 4) != 0);
}
