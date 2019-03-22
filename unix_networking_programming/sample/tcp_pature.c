/*
 *     File Name: tcp_pature.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: Wednesday, March 20, 2019 AM10:36:56 HKT
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h> // bzero
#include <arpa/inet.h>
/*　test 3 time handsake */
#define MAXSIZEDATA 2048
int main(int argc, char **argv)
{
	int socketfd, nbytes;
	char recvline[MAXSIZEDATA + 1];
	struct sockaddr_in serveraddr;

	if (argc != 2){
		perror("Usage, too small ");
		exit(1);
	}

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{

		perror("socket error\n");
		exit(1);
	}

	bzero(&serveraddr, sizeof(serveraddr));
	/* 上面就是一个简单的申请*/
	/* 填充 socket 封装头　*/
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(13);

	if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0){
		perror("inet_pton is error\n");
	}
	/* 如果有domin的话，需要使用 inet_pton 转化为　ip*/
	if (connect(socketfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == -1){
		perror("connect error\n");
		exit(1);
	}

	while(( nbytes = read(socketfd, recvline, MAXSIZEDATA)) > 0){
		recvline[nbytes] = '\0'; /* 网络编程尤其注意这一点　*/
		if (fputs(recvline, stdout) == EOF)
			perror("fputs, error");
	}

	if (nbytes < 0)
		perror("read error\n");

	exit(0);
}

