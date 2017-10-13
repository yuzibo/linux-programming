/*************************************************************************
     File Name: tcpclient.c
     Author: yubo
     Mail: yuzibode@126.com
     Created Time: 2016年02月19日 星期五 01时50分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUFSIZE 512

static void bail(const char *on_what){
	fputs(strerror(errno), stderr);
	fputs(": ", stderr);
	fputs(on_what, stderr);
	fputc('\n', stderr);
	exit(1);
}
int main(int argc, char **argv){
	int sockfd; /* socket of client */
	char buf[BUFSIZE];
	struct sockaddr_in server_addr; /* IP of server*/
	int portnumber;
	struct hostent *host;
	int nbytes;
	int z;
	char reqBuf[BUFSIZE];
	if(argc != 3) {
		fprintf(stderr, "Usage: %s hostname portnumber\a\n",
				argv[0]);
		exit(1);
	}
	if ((host = gethostbyname(argv[1])) == NULL){
		fprintf(stderr, "Gethostname error\n");
		exit(1);
	}
	if ((portnumber = atoi(argv[0])) < 0){
		fprintf(stderr, "Usage: %s hostname portnumber\a\n",argv[0]);
		exit(1);
	}
	/* create socket of client  */
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		fprintf(stderr, "Socket error: %s\a\n",strerror(errno));
		/* strerror return a pointer to string */
	}
	/* create socket of client */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);//?
	/*connect server*/
	if (connect(sockfd, (struct sockaddr*)(&server_addr),
				sizeof(server_addr)) == -1){

		fprintf(stderr,"Connect Error: %s\a\n",strerror(errno));
		exit(1);
	}
	/*
	 * display addr
	 * */
	printf("connected to server %s\n",inet_ntoa(server_addr.sin_addr));
	/* client loop ,when type 'quit' quit */
	for(;;){
		/* input date and time string */
		fputs("\nEnter format string(^D or 'quit' to exit):", stdout);
		if(!fgets(reqBuf, sizeof(reqBuf),stdin)){//?
			printf("\n");
			break;
		}
		/* full with NULL and delete \n*/
		z = strlen(reqBuf);
		if (z > 0 && reqBuf[--z] == '\n')
			reqBuf[z] = 0;
		/* only type ENTER key*/
		if (z == 0)
			continue;
		/* input quit to quit */
		if(!strcasecmp(reqBuf,"QUIT")){
			printf("press any key to quit.\n");
			getchar();
			break;
		}
		/* send  string of date and time to server ,deleted NULL*/

		z = write(sockfd, reqBuf, strlen(reqBuf));
		printf("client has sent '%s' to the server.\n", reqBuf);

		if (z < 0)
			bail("write()");
		/* read content from response server */
		if ((nbytes = read(sockfd, buf, sizeof(buf))) == -1) {
			fprintf(stderr,"Read error: %s\n", strerror(errno));
			exit(1);
		}
		/* if server close connect, the client will handle with it
		 * */
		if (nbytes == 0){

			printf("server has closed the socket.\n");
			printf("press any key to exit...\n");
			getchar();
			break;
		}
		buf[nbytes] = '\0';
		/* output date and time*/
		printf("result from %s port %u : \n\t'%s'\n",
				inet_ntoa(server_addr.sin_addr),
				(unsigned)ntohs(server_addr.sin_port),
				buf);

	}
	close(sockfd);
	return 0;
}

