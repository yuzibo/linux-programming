/*
 *     File Name: ls1.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月07日 星期四 21时22分39秒
 */
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char *);
int main(int argc, char *argv[])
{
	if( argc == 1)
		do_ls(".");
	else
		while(--argc){
			printf("%s:\n",*++argv);
			do_ls(*argv);

		}

}
void do_ls(char *dirname )
{
	/*
	 * list files in directory called dirname
	 */
	DIR *dir_ptr; /* the directory */
	struct dirent *direntp; /* each entry */

	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls1;cannot open %s\n",dirname);
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL)
			printf("%s\n",direntp->d_name);
		closedir(dir_ptr);
	}

}
