/*
 *     File Name: psh1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年05月18日 星期四 07时23分32秒
 *     带提示符的shell编写
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define MAXARGS		20 /* cmdline args */
#define ARGLEN		100 /* token length */

int execute(char *const arglist[])
{
	execvp(arglist[0], arglist);
	perror("execvp failed");
	exit(1);
}

char *makestring(char *buf)
{
	char *cp;
	buf[strlen(buf) - 1] = '\0';
	cp = malloc(strlen(buf) + 1);
	if (cp == NULL) {
		fprintf(stderr, "no memory\n");
		exit(1);
	}

	strcpy(cp, buf);
	return cp;

}

int main()
{
	char *arglist[MAXARGS + 1];
	int numargs;
	char argbuf[ARGLEN]; /* read stuff from here */
	numargs = 0;

	while( numargs < MAXARGS) {
		printf("Arg[%d]?", numargs);
		if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n') {
			arglist[numargs++] = makestring(argbuf);
		}
		else {
			if (numargs > 0) {
			printf("%s", argbuf);
				arglist[numargs] = NULL;
				if (execute(arglist))
				numargs = 0;
			}
		}
	}
	return 0;
}


