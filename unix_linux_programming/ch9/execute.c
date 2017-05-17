/*
 *     File Name: execute.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年05月16日 星期二 05时52分32秒
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


#include "smsh.h"

/*
 * purpose: run a program passing its argument
 * return : status returned via wait or -1 on error
 * errors : -1 on fork() or wait() errors
 *
 */
int execute(char *argv[])
{
	int pid;
	int child_info = -1;

	if (argv[0] == NULL)
		return 0;

	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0) {
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	} else if (wait(&child_info) == -1) {
		perror("wait");
	}

	return child_info;



}
