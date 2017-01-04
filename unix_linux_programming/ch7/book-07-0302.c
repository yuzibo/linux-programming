/*
 *     File Name: book-07-0302.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月02日 星期一 09时09分42秒
 */
#include<stdio.h>
#include<curses.h>
int main()
{
	int i;
	initscr(); /* turn on the screen */

	clear();
	for( i = 0; i < LINES; i++){
		move(i, i + 1);
		if(i % 2 == 0)
			standout(); /*  startup the mode , let screen 反色*/
		addstr("hello, hechun ");
		if(i % 2 == 1)
			standend();/* close the mode */

	}
	refresh();
	getch();
	endwin();
	printf("the lengths of line is %d\n", LINES);
}
