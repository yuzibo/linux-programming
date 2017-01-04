/*
 *     File Name: book-070403.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月03日 星期二 08时06分23秒
 */
#include<stdio.h>
#include<curses.h>
#define	LEFTEDGE	10
#define	RIGHTEDGE	30
#define ROW		10


int main()
{
	char	message[20] = "Hello";
	char	blank[20] = "	";
	int	dir = + 1;
	int	pos = LEFTEDGE;
	initscr();
	clear();
	while(1){
		move(ROW, pos);
		addstr(message);
		move(LINES - 1, COLS - 1);
		refresh(); /* show string */
		sleep(1); /* */
		move(ROW, pos); /* erase string */
		addstr(blank);
		pos += dir;	/* advance position */
		if(pos >= RIGHTEDGE) /* check for bounece */
			dir = -1;
		if(pos <= LEFTEDGE)
			dir = + 1;

	}

}
