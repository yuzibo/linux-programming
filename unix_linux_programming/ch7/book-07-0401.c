/*
 *     File Name: book-07-0401.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月03日 星期二 04时19分29秒
 */
#include<stdio.h>
#include<curses.h>
int main()
{
	int i;
	initscr();

	clear();

	for(i = 0; i < LINES; i++){
		move(i,i + 1);
		if(i%2 == 1)
			standout();
		addstr("Hello, yubo");
		if(i % 2 == 1)
			standend();
		sleep(1);
//		refresh();
	}
	endwin();
}
