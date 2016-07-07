/*
 *     File Name: sol-02-11.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月07日 星期四 07时41分33秒
 */
/*
 *  目的： 没有想到这儿解决方案这么简单。
 *  就是判断一下argv[1]与argv[2]相同吗？
 *
 *
 *   Usage : ./the-exe src-file dest-file
 *
 */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <stdlib.h>

#define BUFSIZE 4096
#define COPYMODE 0644

void  oops(char *,char *);
int main(int argc, char *argv[]){
	int	 in_fd, out_fd, n_chars;
	char	buf[BUFSIZE];
	/*   check args */
	if (argc != 3){
		fprintf(stderr, "Usage: %s source_file destination_file\n", *argv);
		exit(1);
	}
	/*  prevent user from cclobbering a file with itself */
	if (strcmp(argv[1], argv[2]) == 0){
		fprintf(stderr, "cp: `%s` and `%s` are the same file.\n",argv[1], argv[2]);
		exit(1);
	}
	/** open files */
	if ((in_fd = open(argv[1], O_RDONLY)))
		oops("Cannot open", argv[1]);
	if ((out_fd = creat(argv[2], COPYMODE)) == -1)
		oops( "Cannot creat", argv[2]);

	/* copy files */

	while ((n_chars = read(in_fd, buf, BUFSIZE)) > 0)
		if(write(out_fd, buf, n_chars) != n_chars)
			oops("Write error to ",argv[2]);
	if (n_chars == -1)
		oops("Read error from", argv[1]);
	/** close files **/
	if (close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files","");

}
void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ",s1);
	perror(s2);
	exit(1);
}
