/*
 *     File Name: book-06-2.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年08月04日 星期四 22时38分12秒
 */
#include<stdio.h>
#include<ctype.h>
int main()
{
	int c;
	while((c = getchar()) != EOF){
		if (c == 'z')
			c = 'a';
		else if(islower(c))
			c++;
		putchar(c);

	}
}
