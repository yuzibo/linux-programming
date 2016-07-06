/*
 *     File Name: gettime3.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月06日 星期三 02时04分14秒
 */
#include<stdio.h>
#include<time.h>
int main(){
	char *wday[] = {"Sun", "Mon","Tue","Wed","Thu","Fri","Sat"};
	time_t timep;
	struct tm *p;

	time(&timep); /*获得time_t结构的时间， UTC时间*/
	p = gmtime(&timep); /*转化为 struct* tm 结构的时间 */
	printf("%d/%d/%d\n",1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);

	printf("%s %d:%d:%d\n",wday[p->tm_wday], p->tm_hour, p->tm_min,p->tm_sec);
	return 0;


}
