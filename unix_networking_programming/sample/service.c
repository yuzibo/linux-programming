/*************************************************************************
     File Name: service.c
     Author: yubo
     Mail: yuzibode@126.com
     Created Time: 2016年01月05日 星期二 03时57分51秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#define MYPORT 3490 /*开放的端口*/
#define BACKLOG 5
int main ()
{
	int sockfd,new_fd;
	struct sockaddr_in srvaddr;
	struct sockaddr_in cliaddr;
	int sin_size;
	/*create fd of socket*/
	if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) == -1){
		perror("socket error");
		exit(1);
	}
	bzero(&srvaddr,sizeof(srvaddr));
	/*Fill a socket of internet with information*/
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(MYPORT);
	/*BIND() 将服务器的地址和socket bind在一起*/
	if (bind(sockfd, (struct sockaddr *)&srvaddr,sizeof(struct sockaddr))==-1)
		perror("bind error");

	/*listen tell kernel*/
	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen error");
		exit(1);
	}
	for(;;)
	{
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd=accept(sockfd,(struct sockaddr *)&cliaddr,
						&sin_size)) == -1){
			perror("accept error");
		}
		printf("server: got connection from %s\n",inet_ntoa(cliaddr.sin_addr));
		if(write(new_fd,"hello,world,network!\n",14) == -1)
			perror("write error");
		close(new_fd);
	}
}

