/*
 *     File Name: stat1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月07日 星期四 23时48分06秒
 */
#include<stdio.h>
#include<sys/stat.h>
int main()
{
	struct stat infobuf;
	if(stat("/etc/passwd", &infobuf) == -1)
		perror("/etc/passwd");
	else
		printf("The size of /etc/passwd is %d\n",
				infobuf.st_size);

}
