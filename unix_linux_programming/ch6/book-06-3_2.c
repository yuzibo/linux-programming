/*
 *     File Name: book-06-3_2.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年08月05日 星期五 00时00分24秒
 */
#include<stdio.h>
#include <termios.h>

#define QUESTION	"Do you want another transaction"

int get_response(char *);
void set_crmode();
int tty_mode(int);

int main()
{
	int response;
	tty_mode(0);
	set_crmode;
	response = get_response(QUESTION);
	tty_mode(1);
	return response;
}
int get_response(char *question)
{
	int input;
	printf("%s(y/n)?", question);
	while(1){
		switch(input = getchar()){
			case 'Y':
			case 'y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;
			default:
				  printf("\n cannot understand %c", input);
				  printf("Please type y or no \n");
		}
	}
}
/*
 * purpose: put file description 0(i.e stdin) into chr-by-chr mode
 * method: use bits in termios
 */
void set_mode()
{
	struct termios	ttystate;
	tcgetattr(0, &ttystate); /* read cur . setting*/
	ttystate.c_lflag	&= ~ICANON; /* no buffering */
	ttystate.c_cc[VMIN]	= 1; /* get 1 char at a time */
	tcsetattr(0, TCSANOW, &ttystate); /* install setting*/
}

int tty_mode(int how)
{
	static struct termios original_mode;
	if(how == 0)
		tcgetattr(0, &original_mode);
	else
		return tcsetattr(0, TCSANOW, &original_mode);
}
