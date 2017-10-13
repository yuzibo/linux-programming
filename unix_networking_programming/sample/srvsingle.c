/*************************************************************************
     File Name: srvsingle.c
     Author: yubo
     Mail: yuzibode@126.com
     Created Time: 2016年02月18日 星期四 19时34分02秒
     This is stream socket server
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<inttypes.h>

#define BUFSIZE 512

/* error report */
static void bail(const char *on_what){
	fputs(strerror(errno),stderr);//?
	fputs(": ", stderr);
	fputs(on_what, stderr);
	fputc('\n',stderr);

	exit(1);
}
int main(int argc, char **argv){
	int sockfd;/* sock of server*/
	int new_fd;/* connection of server*/
	struct sockaddr_in server_addr;/* socket of listen of server*/
	struct sockaddr_in client_addr;/* IP of client*/

	socklen_t size;
	int portnumber;

	char reqBuf[BUFSIZE]; /*cache of receive application*/
	char dtfmt[BUFSIZE]; /* string of data-time */
	time_t td; /*currently time and date*/
	struct tm tm; /*struct of time*/
	int z;
	if (argc != 2){
		fprintf(stderr, "Usage: %s portnumber \a\n",argv[0]);
		exit(1);
	}
	if ((portnumber = atoi(argv[1])) < 0){
		fprintf(stderr, "Usage: %s portnumber \a\n",argv[0]);
		exit(1);
	}
	/* crete socket*/
	if ((sockfd = socket(PF_INET,SOCK_STREAM, 0)) == -1){
		fprintf(stderr, "socket error: %s\a\n",strerror(errno));
		exit(1);
	}
	/* ready listen socket IP and port*/
	memset(&server_addr, 0, sizeof (server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(portnumber);

	/* bind socket*/
	if ((bind(sockfd, (struct sockaddr *)(&server_addr),sizeof(server_addr))) == -1){
		fprintf(stderr,"bind error: %s\a\n",strerror(errno));
		exit(1);
	}
	/* listen */
	if(listen(sockfd, 128) == -1){
		fprintf(stderr, "listen error: %s\n\a", strerror(errno));
		exit(1);

	}
	printf("waiting for the client's request...\n");
	while(1) {
		size = sizeof(struct sockaddr_in);
		/* receive a client connect and create socket*/
		if((new_fd = accept(sockfd, (struct sockaddr *)(&client_addr),&size))== -1){
			fprintf(stderr,"Accept error: %s\a\n",strerror(errno));
			exit(1);


	}
	fprintf(stdout, "Server got connection from %s\n",
		inet_ntoa(client_addr.sin_addr));
	for(;;){
		/* read date and time request from client
		 * if there is no data,quit
		 *
		 * */
		z = read(new_fd, reqBuf, sizeof(reqBuf));
		if (z < 0)
			bail("read()");
		if (z == 0){
			close(new_fd);
			break;
		}
		/* full with NULL*/
		reqBuf[z] = 0;
		/*
		 * request server's date and time
		 */
		time(&td);
		tm = *localtime(&td);

		/* according to string of date-time genater
		 * response's string
		 * */
		strftime(dtfmt, /* result of format */
			sizeof(dtfmt),
			reqBuf,
			&tm);
		/* send to client */
		z = write (new_fd, dtfmt, strlen(dtfmt));
		if (z < 0)
			bail("write()");


	      }
	}
}

