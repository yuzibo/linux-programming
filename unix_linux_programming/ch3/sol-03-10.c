/*
 *     File Name: sol-03-10.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月11日 星期一 22时35分39秒
 */
/* A version of ls that print the list in multiple columns
 * is :
 * The version fixes the number of columns at lest at 80.
 * In a later chapter we see how to ask the system for the width of
 * the terminal display
 * HOW: read all names into an array that grows Keep track of
 * longest filename, use that to determine column width
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

#define SCREEN_WIDTH	80
void do_ls(char []);
void fatal(char *,char *);
void list_init();
void list_show();
void list_finish();
void list_append(char *);
int get_screen_width();

int main(int argc, char *argv[]){
	if (argc == 1)
		do_ls(".");
	else
		while(--argc){
		printf("%s:\n",*++argv);
		do_ls(*argv);
		}

}
void do_ls(char dirname[])
/*
 * list files in directory called dirname
 */
{
	DIR *dir_ptr;
	struct dirent *direntp;
	list_init();
	if ((dir_ptr = opendir(dirname)) == NULL)
		fatal("cannot open", dirname);
	else {
		while((direntp = readdir(dir_ptr)) != NULL)
			list_append(direntp->d_name);
		closedir(dir_ptr);
	}
	list_show();
	list_finish();
}


void *emalloc(unsigned), *erealloc(void*, unsigned);
char **namelist = NULL;
int listlen = 0;
int taken = 0;

#define CHUNKLEN	100

void list_init()
{
	namelist = (char **)emalloc(CHUNKLEN * sizeof(char *));
	listlen = CHUNKLEN;
	taken = 0;
}

/*
 * add an item to the list, extending it if needed
 *
 */
void list_append(char *str)
{
	char *newstring(char *);
	char *name = newstring(str);

	if (taken == listlen) {
		listlen += CHUNKLEN;
		namelist = (char **) erealloc(namelist, listlen);
	}
	namelist[taken++] = name;


}
/*
 * figure out max length,then figure out number of cols we can do
 * and then list them
 *
 */
void list_show()
{
	int i;
	int maxlen = 0;
	int pagewidth;
	int cols, col_len, col_wid;
	int row, col;
	char *name;
	/* figure out lengths and widths of columns */
	for( i = 0; i < taken; i++)
		if(strlen(namelist[i]) > maxlen)
			maxlen = strlen(namelist[i]);

	col_wid = maxlen + 1;
	pagewidth = get_screen_width();
	cols = pagewidth / col_wid;
	col_len = taken / cols;

	if(taken % cols)
		col_len++;
	/* print the list using these numbers */
	for (row = 0; row < col_len; row++)
		for(col = 0; col < cols; col++){
			i = row + col*col_len;
			if (i < taken){
				if(i + col_len < taken)
					printf("%-*s",col_wid, namelist[i]);
				else
					printf("%s\n",namelist[i]);
			}
		}
}

/*
 * delete the words and list
 */
void list_finish(){
	int i;

	for (i = 0; i < taken; i++)
		free(namelist[i]);
	free(namelist);
	namelist = NULL;
	taken = listlen = 0;
}
int get_screen_width()
{
	return SCREEN_WIDTH;
}
/*
 * construct a string
 */
char *newstring(char *s)
{
	char *rv = emalloc(1 + strlen(s));
	strcpy(rv, s);
	return rv;
}
void  *emalloc(unsigned n)
{
	void *rv = malloc(n);
	if(rv)
		return rv;
	fatal("out of memory","");
}
void *erealloc(void *p, unsigned n)
{
	void *rv = realloc(p, n);
	if(rv)
		return rv;
	fatal("out of memory", "");
}
/*
 * report and die
 */
void fatal(char *s1, char *s2)
{
	fprintf(stderr, "ls1: %s%s\n",s1,s2);
	exit(1);
}
