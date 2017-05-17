/*
 *     File Name: splitline.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年05月16日 星期二 06时33分42秒
 *     -command reading and parsing functions for smsh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smsh.h"
/*
 * char *next_cmd : read next command line from fp
 * returns	  : dynamiclly allocated string holding the message
 * errors	  : NULL at EOF or call fatal() from emalloc()
 *
 */
char *next_cmd(char *prompt, FILE *fp)
{
	char *buf;
	int bufspace = 0;
	int pos = 0;
	int c;

	printf(">\n");

	while((c = getc(fp)) != EOF) {
		/*
		 * need space
		 */
		if (pos + 1 >= bufspace) {
			if (bufspace == 0)
				buf = emalloc(BUFSIZ);
			else buf = erealloc(buf, bufspace + BUFSIZ);

			bufspace += BUFSIZ;
		}
		if (c == '\n')
			break;
		/* no : add into buf */
		buf[pos++] = c;

	}
	if (c == EOF && pos == 0)
		return NULL;

	buf[pos] = '\0';

	return buf;

}

/*
 * splitline.c : parse a line into an array of strings
 *
 */

#define is_delim(x) ((x) == ' ' || (x) == '\t')

/* purpoose: split a line into array of white-space separated tokens
 * return  : a NULL - terminated array of pointers to copied of the token or		NULL if line if no tokens on the line
 * action  : traverse the array, locate strings, make copies
 * notes   : strtok() could work, but we want to add quotes later
 */

char **splitline(char *line)
{
	char **args;

	int spots = 0; /* spots in table */
	int bufspace = 0;
	int argnum = 0;
	char *cp = line;
	char *start;
	int len;


	if (line == NULL)
		return NULL;

	args = emalloc(BUFSIZ);

	bufspace = BUFSIZ;

	spots = BUFSIZ/sizeof(char *);

	while( *cp != '\0') {
		while(is_delim(*cp))
			cp++;
		if (*cp == '\0')
			break;
		/*  make sure the array has room (+1 for NULL) */
		if (argnum + 1 >= spots) {
			args = erealloc(args, bufspace + BUFSIZ);
			bufspace  += BUFSIZ;
			spots += (BUFSIZ/sizeof(char *));
		}

		start = cp;
		len = 1;
		while(*++cp != '\0' && !(is_delim(*cp)))
			len++;
		args[argnum++] = newstr(start, len);
	}
	args[argnum] = NULL;
	return args;
}

/*
 * purpose: constructor for string
 * return : a string, never NULL
 */

char *newstr(char *s, int l)
{
	char *rv = emalloc(l + 1);
	rv[l] = '\0';

	strncpy(rv, s, l);
	return rv;

}

void freelist(char **list)
{
	char **str = list;

	while(*str)
		free(*str++);
	free(list);
}

void *emalloc(size_t n)
{
	void *rv;
	if ((rv = malloc(n)) == NULL)
		fatal("out of the memmory"," ", 1);
	return rv;
}

void *erealloc(void *p, size_t n)
{
	void *rv;
	if ((rv = realloc(p, n)) == NULL)
		fatal("realloc failed", " ", 1);
	return rv;

}


