/*
 *     File Name: cp2-3.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月01日 星期五 03时23分30秒
 *
 *   将文件内容复制到dev/tty
 *   Usage: ./cp2-3 filename
 *
 *   就会在频幕上显示出来，因为我让他复制到 /dev/tty
 */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFFERSIZE	4096
#define COPYMODE	0644

void oops(char *,char *);
int main(int argc, char *argv[])
{
	int	in_fd, out_fd, n_chars;
	char	buf[BUFFERSIZE];

	if(argc != 2){
		fprintf(stderr, "Usage: %s source destinations\n", *argv);
		exit(1);
	}
	if((in_fd = open(argv[1],O_RDONLY)) == -1)
		oops("CAnnot open",argv[1]);
	if ((out_fd = open("/dev/tty",O_RDWR)) == -1)
		oops("Cannot open",argv[2]);

	while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if(write(out_fd, buf, n_chars) != n_chars){
			oops("Write error to ","/dev/tty");
		}
	if(n_chars == -1)
		oops("Read error from ",argv[1]);
	if(close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error on closing files"," ");

}
void oops(char *s1, char *s2){
	fprintf(stderr,"Error:%s",s1);
	perror(s2);
	exit(1);
}

