/*
 *     File Name: ls2.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月08日 星期五 07时31分15秒
 */

/*
 * notes: use stat and pwd.h and grp.h
 * BUG: try ls2 /tmp
 */
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<time.h>

void do_ls(char *);
void do_stat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int ,char []);
/* last access time */
void show_file_time(time_t);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char *argv[])
{
	if(argc == 1)
		do_ls(".");
	else
		while(--argc){
			printf("%s\n",*++argv);
			do_ls(*argv);
		}
}
void do_ls(char dirname[])
	/*
	 * list files in directory called dirname
	 */
{
	DIR *dir_ptr;	/* the directory */
	struct dirent *direntp;	/* each entry */
	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls2: cannot open %s\n",dirname);
	else
	{
		while((direntp = readdir(dir_ptr)) != NULL)
			do_stat(direntp->d_name);
		closedir(dir_ptr);
	}
}
void do_stat(char *filename)
{
	struct stat info;
	if (stat(filename, &info) == -1)
		perror(filename);
	else
		show_file_info(filename, &info);
}
void show_file_info(char *filename, struct stat *info_p)
/*
 * display the info about filename. The info is stored in struct
 * at *info_p
 *
 */
{
	char modestr[11];

	mode_to_letters(info_p->st_mode, modestr);
	printf("%s ", modestr);
	printf("%-4d",(int)info_p->st_nlink);
	printf("% - 8s", uid_to_name(info_p->st_uid));
	printf("% - 8s",gid_to_name(info_p->st_gid));
	show_file_time(info_p->st_mtime);
	printf("%8ld",(long)info_p->st_size);
	printf(" % - 8s\n", filename);
}
void show_file_time(time_t st_mktime)
{
/*
 * Here, there are two problems:
 * first. No matter use st_xtime  and return the same time;
 *  Two:  I delete the '\0' that end with returned chars.
 *
 *
 */
	time(&st_mktime);
	char *str  = ctime(&st_mktime) + 10;
	int len = strlen(str),i;
	for(i = 0; i < len; i++)
		;
	str[i-1] = ' ';
	printf("% - 8s",str);

}
void mode_to_letters(int mode, char str[])
{
	strcpy(str, "----------");
	if( S_ISDIR(mode)) str[0] = 'd';
	if( S_ISCHR(mode)) str[0] = 'c';
	if( S_ISBLK(mode)) str[0] = 'b';

	if(mode & S_IRUSR) str[1] = 'r';
	if(mode & S_IWUSR) str[2] = 'w';
	if(mode & S_IXUSR) str[3] = 'x';

	if(mode & S_IRGRP) str[4] = 'r';
	if(mode & S_IWGRP) str[5] = 'w';
	if(mode & S_IXGRP) str[6] = 'x';

	if(mode & S_IROTH) str[7] = 'r';
	if(mode & S_IWOTH) str[8] = 'w';
	if(mode & S_IXOTH) str[9] = 'x';

}
# include<pwd.h>
char *uid_to_name(uid_t uid)
	/*
	 * returns pointer to username associated with
	 * uid, uses getpw()
	 */
{
	struct passwd  *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL){
		sprintf(numstr, "%d",uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}

#include<grp.h>
char *gid_to_name(gid_t gid)
/*
 * reurns pointer to group number gid, used getgrgid(3)
 *
 */
{
	struct group  *grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL){
		sprintf(numstr, "%d",gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
/**/
