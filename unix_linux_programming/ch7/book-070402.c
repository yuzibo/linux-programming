/*
 *     File Name: book-070402.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月03日 星期二 07时43分31秒
 */
/*
 * 效果实现了动态的效果
 * */
#include<stdio.h>
#include<curses.h>

int main()
{
	int i;

	initscr();

	clear();

	for(i = 0; i < LINES; i++){
		move(i, i + 1);
		if(i % 2 == 1)
			standout();
		addstr("hello, hechun ");
		if(i % 2 == 1)
			standend();
		refresh();
		sleep(1);
		move(i, i + 1);
		addstr("          ");

	}
	endwin();
}
