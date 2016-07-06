/*
 *     File Name: strftime.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月05日 星期二 22时35分37秒
 */
/*   Usage: ./exe '%Y'   //会显示当前的年 （year）
 *   这里有点涉及printf的格式输出，细节略过不表
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char *argv[]){

	char outstr[200];
	time_t t;
	struct tm *tmp;
	t = time(NULL);
	tmp = localtime(&t);
	if (tmp == NULL) {
		perror("localtime");
		exit(EXIT_FAILURE);

	}
	if (strftime(outstr, sizeof(outstr), argv[1], tmp) == 0){
		fprintf(stderr, "strftime return 0");
		exit(EXIT_FAILURE);
	}
	printf("Result string is  \"%s\"\n", outstr);
	exit(EXIT_SUCCESS);




}
