/*
 *     File Name: smsh.h
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年05月16日 星期二 07时24分08秒
 */
#define YES 1
#define  NO 0

char *next_cmd();
char **splitline(char *);
void freelist(char **);
void *emalloc(size_t n);
void *erealloc(void *, size_t);
int execute(char **);
void fatal(char *, char *, int);
char *newstr(char *, int);



