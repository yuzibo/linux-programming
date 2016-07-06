/*
 *     File Name: strptime.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月05日 星期二 21时39分02秒
 */
#include<stdio.h>
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	struct tm tm;
	char buf[256];

	memset(&tm, 0, sizeof(struct tm));
	strptime("2016-07-06 09:53:24", "%Y-%m-%d %H:%M:%S",&tm);

	strftime(buf, sizeof(buf),"%d %b %Y %H:%M",&tm);
	puts(buf);
	exit(EXIT_SUCCESS);


}
