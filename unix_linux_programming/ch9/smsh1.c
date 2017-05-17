/*
 *     File Name: smsh1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年05月16日 星期二 05时35分31秒
 */
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "smsh.h"

#define DFL_PROMPT	">"

void setup();

int main()
{
	char *cmdline, *prompt, **arglist;
	int result;

	setup();

	while ((cmdline = next_cmd(prompt, stdin)) != NULL) {
		if (( arglist = splitline(cmdline)) != NULL) {
			result = execute(arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return 0;

}

/*
 * purpose: initialize shell
 * return : nothing. calls fatal() if trouble
 *
 */
void setup()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s, %s\n", s1, s2);
	exit(n);

}

