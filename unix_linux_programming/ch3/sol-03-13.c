/*
 *     File Name: sol-03-13.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月13日 星期三 21时31分12秒
 */
/*
 * modify the before version of cp. If your dest address is a
 * directory, then you put the src file into the dir.
 *
 *	Usage: ./exe src dest
 *	if dest names a directory, then copy src to dest/src
 *	NOTE: if src has a leading path ,
 *	then nly use last component
 */
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

#define BUFFERSIZE	4096
/*
 * note: the real copy takes the mode of the copy from
 *	the mode of the source
 *
 */

#define COPYMODE 0644

void oops(char *, char *);

char *make_destfilename(char *, char *);
void do_copy(char *, char *);

int main(int argc, char *argv[])
{
	if (argc != 3){
		fprintf(stderr, "usage: %s source destination\n",*argv);
		exit(1);
	}
	do_copy(argv[1], argv[2]);
	return 0;
}
/*
 * Copies a file from src to dest
 * If dest is a directory, the do_copy() copies to a file
 * in dest with the name taken from the filename for src
 */
void do_copy(char *src, char *dest)
{

	int	in_fd, out_fd, n_chars;
	char	buf[BUFFERSIZE];

	char *destfilename = make_destfilename(src, dest);

	/*
	 * open files
	 */
	if ((in_fd = open(src, O_RDONLY)) == -1)
		oops("cannot open", src);

	if ((out_fd = creat(destfilename, COPYMODE)) == -1)
		oops("Cannot creat", destfilename);

	/*
	 * copy files
	 *
	 */
	while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if (write( out_fd, buf, n_chars) != n_chars)
			oops("Write error to ", destfilename);

	if (n_chars == -1)
		oops("READ error from",src);
	/*
	 * close files
	 */
	if ( close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");

}
void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s",s1);
	perror(s2);
	exit(1);
}
/*
 * If dest is a dir, then combine src and dest
 *
 */

char *make_destfilename(char *src, char *dest)
{
	struct stat info;
	char *srcfilename;
	char *recv;

	if( stat(dest, &info) == -1)
		return dest;

	if (! S_ISDIR(info.st_mode))
		return dest;
	/* find last component of source name */
	if ((srcfilename = strrchr(src, '/')) != NULL)
		srcfilename++;
	else
		srcfilename = src;
	/* use that to construct target name */
	recv = malloc(strlen(srcfilename) + 2 + strlen(dest));
	if (recv == NULL)
		oops("Out of memory" ,"");
	sprintf(recv, "%s/%s", dest, srcfilename);
	return recv;
}
