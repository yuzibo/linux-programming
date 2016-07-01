/*
 *     File Name: who1.c
 *     和 utmplib.c文件一起使用的
 *	使用了缓冲技术
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年06月29日 星期三 09时45分17秒
 */
#include<stdio.h>
#include<string.h>
#include<utmp.h>
//#include<readutmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>


#define SHOWHOST

#define UT_TIME_MEMBER(UT_PTR) ((UT_PTR)->ut_tv.tv_sec)

void show_info(struct utmp * utmpfd);
void show_time(struct utmp *utmpfd);
int main(){
	struct utmp *utbufp,
		    *utmp_next();
	if(utmp_open(UTMP_FILE) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while((utbufp = utmp_next()) != ((struct utmp *) NULL))
		show_info(utbufp);
	utmp_close();
	return 0;
}
void show_info(struct utmp *utmpfd)
{
	if(utmpfd->ut_type != USER_PROCESS)
		return;
	printf("% - 8.8s", utmpfd->ut_user);
	printf(" ");
	printf("% - 8.8s",utmpfd->ut_line);
	printf(" ");
//	printf("% - 8.8s", utmpfd->ut_time);
	printf(" ");
	show_time(utmpfd);

#ifdef SHOWHOST
	printf("(%s)",utmpfd->ut_host);
#endif
	printf("\n");
}
void show_time(struct utmp *utmpfd)
{
	time_t tm = UT_TIME_MEMBER(utmpfd);
	char *ptr =  ctime(&tm) + 4;
	ptr[16] = '\0';
	printf("%s",ptr);

/*	int len = strlen(ptr);
 *	printf("The length of time is %D\n",len);
 */
}
