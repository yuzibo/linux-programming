/*
 *     File Name: gettime1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月06日 星期三 01时19分24秒
 */
#include<stdio.h>
#include<time.h>
int main(){
	time_t timep;
	time(&timep); /* 获取time_t 类型的当前时间  */
	printf("%s\n",asctime(gmtime(&timep)));
	/* 使用gtime将time_t类型的时间转换为
	 * struct tm类型的时间，然后再用asctime转换为
	 * 我们常见的格式: Fri Wed Jul  6 05:40:11 2016
	 *
	 */
	return 0;

}
