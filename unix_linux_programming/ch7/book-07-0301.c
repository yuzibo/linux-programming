/*
 *     File Name: book-07-0301.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年01月02日 星期一 08时55分16秒
 *     用法：
 *     gcc -o exe -lcurses -g source.c
 *
 *	链接curses.h文件
 *
 *	这里大约9个函数，都是类似，需要记住
 */
#include<stdio.h>
#include<curses.h>

int main()
{
	initscr();/* turn on curses */
	clear(); /* clear screen */
	move(10, 20); /* row10, col20 */
	addstr("Hello,yubo");
	move(LINES - 1, 0);/* move to LL*/
	refresh(); /* update the screen */
	getch(); /* wait the input user */
	endwin(); /* close the screen */
}
