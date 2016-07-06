/*
 *     File Name: gettime2.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月06日 星期三 01时46分41秒
 */
#include<stdio.h>
#include<time.h>
int main(){
	time_t timep;
	time(&timep); /* 获取time_t类型的当前时间*/
	printf("%s\n",ctime(&timep));
	/*转换为常见的字符串 Wed Jul  6 01:49:11 2016 */
	return 0;

}
