/*
 *     File Name: sol-03-11.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月12日 星期二 02时09分26秒
 */
/*
 * A corrected version of ls2.c
 * This program combines the directory name with the filename as
 * an argument to stat can find the file.
 * NOTE 1 : uses stat and pwd.h and grp.h
 *      2 : Here, i have completed _ctime_ function in st_xtime in
 *    		stat.
 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>

void do_ls(char []);
void do_stat(char *,char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char []);
void show_file_time(time_t);

char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char *argv[])
{
	if (argc == 1)
		do_ls(".");
	else
		while( --argc){
			printf("%s:\n",*++argv);
			do_ls(*argv);
		}
}
void do_ls( char dirname[])
/*
 * list files in directory called dirname
 */
{
	DIR *dir_ptr;
	struct dirent *direntp;
	char  *fullpath;

	fullpath = (char *)malloc(strlen(dirname) + 1 + MAXNAMLEN  + 1);
	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls2: cannot open %s\n", dirname);
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL){
			sprintf(fullpath, "%s/%s",dirname, direntp->d_name);
			do_stat(fullpath, direntp->d_name);
		}
		closedir(dir_ptr);
	}
}
void do_stat(char *fullpath, char *filename)
{
	struct stat info;

	if (stat(fullpath, &info) == -1)
		perror(filename);
	else
		show_file_info(filename, &info);

}
void show_file_info(char *filename, struct stat *info_p)
/*
 * display the information about 'filename'. The info is stored
 * in *info_p
 *
 */
{
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	char modestr[11];

	mode_to_letters( info_p -> st_mode, modestr);

	printf(" %s"  , modestr);
	printf("%4d " , (int)info_p->st_nlink);
	printf("%-8s ", uid_to_name(info_p->st_uid));
	printf("%-8s ", gid_to_name(info_p->st_gid));
	printf("%8ld ", (long)info_p->st_size);
	printf("%.12s\t", 4+ctime(&info_p->st_atime));
	printf("%s\n ", filename);
}
/*
 * utility functions
 */
/*
 * This function takes a mode value and a char array
 * and puts into the char array ...
 * NOTE: It does not code setuid setgid and sticky
 *
 */
void  mode_to_letters(int mode, char str[])
{
	strcpy(str, "----------"); /* default = no */
	if( S_ISDIR(mode)) str[0] = 'd';
	if( S_ISCHR(mode)) str[0] = 'c';
	if( S_ISBLK(mode)) str[0] = 'b';

	if( mode & S_IRUSR) str[1] = 'r';
	if( mode & S_IWUSR) str[2] = 'w';
	if( mode & S_IXUSR) str[3] = 'x';

	if( mode & S_IRGRP) str[4] = 'r';
	if( mode & S_IWGRP) str[5] = 'w';
	if( mode & S_IXGRP) str[6] = 'x';

	if( mode & S_IROTH) str[7] = 'r';
	if( mode & S_IWOTH) str[8] = 'w';
	if( mode & S_IXOTH) str[9] = 'x';

}

#include <pwd.h>
char *uid_to_name(uid_t uid)
/*  display  uid_t st_uid
 *  uses getpw();
 */
{
	struct passwd *pw_ptr;
	static char numstr[10];

	if ((pw_ptr= getpwuid(uid)) == NULL){
		sprintf(numstr,"%d",uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

#include <grp.h>
char *gid_to_name(gid_t gid)
/*  the same as above
 *
 */
{	struct group *grp_ptr;
	static char numstr[10];

	if ((grp_ptr = getgrgid(gid)) == NULL){
			sprintf(numstr, "%d",gid);
		return numstr;
	}
	else
		 return grp_ptr->gr_name;
}

