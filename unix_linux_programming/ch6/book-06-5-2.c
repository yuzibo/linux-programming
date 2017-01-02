/*
 *     File Name: book-06-5-2.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月01日 星期日 01时30分14秒
 *     为处理好信号做好准备
 */
#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>

#define ASK	"Do you want another transaction"
#define TRIES	3
#define SLEEPTIME	2 /* time per try */
#define BEEP	putchar('\a') /* alter user */

/**
 * 抛弃非法字符，y Y n N 和EOF
 */
int get_ok_char()
{
	int c;
	while((c = getchar()) != EOF && strchr("yYnN",c) == NULL);
	return c;

}
int get_response(char *question, int maxtries)
/*
 * ask a user and wait for answer
 *
 */
{
	int input;
	printf("%s(y/n)?", question);
	fflush(stdout);
	while(1){
		sleep(SLEEPTIME);
		input = tolower(get_ok_char());
		if(input == 'y')
			return 0;
		if(input == 'n')
			return 1;
		if(maxtries-- == 0)
			return 2;
		BEEP;
	}
}
void set_cr_noecho_mode()
{
	struct termios ttystate;
	ttystate.c_lflag &= ~ICANON; /* 非标准模式 */
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &ttystate); /*安装设置 */

}
void set_nodelay_mode()
/*  将标准输入设置为非阻塞输入
 *
 * */
{
	int termflags;
	termflags = fcntl(0, F_GETFL); /* read currently setting */
	termflags |= O_NDELAY;
	fcntl(0, F_SETFL, termflags); /* 安装现在的环境 */


}
void tty_mode(int how)
{
	static struct termios original_mode;
	static int original_flags;
	static int stored = 0;
	if(how == 0){
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
		stored = 1;

	}
	else if (stored){
		tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);

	}
}
void ctrl_c_handler(int signum)
{
	tty_mode(1);
	exit(1);
}
int main()
{
	int response;
	tty_mode(0);
	set_cr_noecho_mode();
	set_nodelay_mode();
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	response = get_response(ASK, TRIES);
	tty_mode(1);
	return response;
}
