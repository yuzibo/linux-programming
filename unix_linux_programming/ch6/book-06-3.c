/*
 *     File Name: book-06-3.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *
 *     Created Time: 2016年08月04日 星期四 23时45分59秒
 *	Purpose: ask if user wants another transaction
 *	这个程序只会简单的处理两种情况
 *	v2会显示输入的字符
 */
#include<stdio.h>
#include<termios.h>

#define QUESTION "Do you want another transaction"
int get_response(char *);

int main()
{
	int response;
	response = get_response(QUESTION);
	return response;
}
/*
 *  ask a question and wait for a y/n answer
 */
int get_response(char *question)
{
	printf("%s(y/n)?", question);
	while(1){
		switch(getchar()){
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N':
			case EOF: return 0;
			default: break;
		}
	}
}

