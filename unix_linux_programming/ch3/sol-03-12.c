/*
 *     File Name: sol-03-12.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月12日 星期二 05时19分30秒
 */
 /*
  *  The version of _ls_ modifies problem about follow:
  *   cannot display suid,guid and sticky bits
  */

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
  #include<sys/types.h>
  #include<dirent.h>
  #include<sys/stat.h>


  void do_ls(char dirname[]);
  void do_stat(char *, char *);
  void show_file_info(char *, struct stat *);
  void mode_to_letters(int mode, char []);
  char *uid_to_name(uid_t );
  char *gid_to_name(gid_t);

  int main(int argc, char *argv[]){
  	if ( argc == 1)
  		do_ls(".");
  	else
  		while(--argc){
  				printf("%s:\n",*++argv);
  				do_ls(*argv);

  	}

  }
  void do_ls(char dirname[])
  {
  	DIR *dir_ptr;
	struct dirent *direntp;
	char	*fullpath;
	fullpath = (char *)malloc(strlen(dirname) + 1 + MAXNAMLEN + 1);
	if ((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls2: cannot open %s\n",dirname);
	else{
		while((direntp = readdir(dir_ptr)) != NULL){
			sprintf(fullpath, "%s/%s",dirname, direntp->d_name);
			do_stat(fullpath, direntp->d_name);
		}
		closedir(dir_ptr);
	}


  }
void do_stat(char *fullpath, char  *filename)
{
	struct stat info;

	if (stat(fullpath, &info) == -1)
		perror(filename);
	else
		show_file_info(filename, &info);
}
void show_file_info(char *filename, struct stat *info_p)
{
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	char modestr[11];
	mode_to_letters( info_p->st_mode, modestr);

	printf( "%s"	, modestr);
	printf( "%4d\t"	, (int) info_p->st_nlink);
	printf( "%-8s"	, uid_to_name(info_p->st_uid));
	printf( "%--8s"  , gid_to_name(info_p->st_gid));
	printf( "%8ld\t"  , (long)info_p->st_size);
	printf( "%.12s\t" , 4+ctime(&info_p->st_mtime));
	printf( "%s\n" , filename);
}

/* This  function takes a mode value and a char array
 * and puts into the char array the file type and the
 * nine letters that correspond to the bits n mode.
 * _NOTES_: It now codes suid \ sgid \ and sticky bits
 */
void mode_to_letters(int mode, char str[])
{
	strcpy( str, "----------");
	if ( S_ISDIR(mode)) str[0] = 'd';
	if ( S_ISCHR(mode)) str[0] = 'c';
	if ( S_ISBLK(mode)) str[0] = 'b';

	if (mode & S_IRUSR) str[1] = 'r';
	if ( mode & S_IWUSR) str[2] = 'w';
	if ((mode & S_ISUID) && (mode & S_IXUSR))
		str[3] = 's';
	else if ((mode & S_ISUID) && !(mode & S_IXUSR))
		str[3] = 's';
	else if (mode & S_IXUSR)
		str[3] = 'x';


	if ( mode & S_IRGRP)
		str[4] = 'r';
	if ( mode & S_IWGRP)
		str[5] = 'w';
	if ((mode & S_ISGID) && (mode & S_IXGRP))
		str[6] = 's';
	else if (( mode & S_ISGID) && !(mode & S_IXGRP))
		str[6] = 's';
	else if (mode & S_IXGRP)
		str[6] = 'x';

	if (mode & S_IROTH) str[7] = 'r';
	if (mode & S_IWOTH) str[8] = 'w';
	if ((mode & S_ISVTX) && !(mode & S_IXOTH))
		str[9] = 't';
	else if ((mode & S_ISVTX) && (mode & S_IXOTH))
		str[9] = 'T';
	else if  ((mode & S_IXOTH))
		str[9] = 'x';
}
#include  <pwd.h>
char *uid_to_name(uid_t uid)
{
	struct passwd *pw_ptr;
	static char numstr[10];
	if (( pw_ptr = getpwuid(uid)) == NULL){
		sprintf(numstr, "%d",uid);
		return numstr;

	}
	else
		return pw_ptr->pw_name;

}
#include <grp.h>
char *gid_to_name(gid_t gid)
{
	struct group *grp_ptr;
	static char numstr[10];
	if (( grp_ptr = getgrgid(gid)) == NULL){
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;

}
