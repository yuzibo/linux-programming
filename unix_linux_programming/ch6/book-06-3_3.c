/*
 *     File Name: book-06-3_3.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年08月05日 星期五 02时44分02秒
 *     这个版本的代码是为了能快速响应，按下其他的非法键
 *     没有回显，但是只要正确的键会立马返回
 */
#include<stdio.h>
#include <termios.h>

#define QUESTION "Doyou want another transaction?"

int get_response(char *);
void set_cr_noecho_mode(void);
int tty_mode(int );

int main()
{
	int response;
	tty_mode(0); /* save mode*/
	set_cr_noecho_mode();/* set -icanon, - echo*/
	response = get_response(QUESTION); /* get some answer */
	tty_mode(1);
	return  response;


}
int get_response(char *question)
{
	printf("%s(y/n)?", question);
	while(1){
		switch(getchar()){
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;

		}
	}
}
/*
 * put file descripton 0 into chr-by-chr mode and noecho mode
 */
void set_cr_noecho_mode()
{
	struct termios ttystatus;
	tcgetattr(0, &ttystatus); /* read curr .setting*/
	ttystatus.c_lflag &= ~ICANON; /* no buffering */
	ttystatus.c_lflag &= ~ECHO; /* no echo either */
	ttystatus.c_cc[VMIN] = 1; /* get 1 char at a time */
	tcsetattr(0, TCSANOW, &ttystatus); /* install setting */
}
/*
 * how == 0 save current original_mode ,
 * how == 1 restore mode
* */
int tty_mode(int how)
{
	static struct termios original_mode;
	if (how == 0)
		tcgetattr(0, &original_mode);
	else
		return tcsetattr(0, TCSANOW, &original_mode);
}
