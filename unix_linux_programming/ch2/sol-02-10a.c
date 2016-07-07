/*
 *     File Name: sol-02-10a.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月07日 星期四 03时52分05秒
 */
/*
 * call ttyname to find the path to our terminal,
 * then only print the entry in utmp for thzt terminal
 *
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<utmp.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>

void showtime(long);
void show_info(struct utmp *);
char *whats_my_line(int);

int main(int argc, char *argv[])
{
	struct utmp utbuf; /* read info from here */
	int utmpfd; /* read from the fd */
	char *myline = NULL; /* used for who am i logic */
	if( argc == 3)
		myline = whats_my_line(0);
	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
		if (myline == NULL || strcmp(utbuf.ut_line,myline) == 0)
			show_info(&utbuf);
	close(utmpfd);
	return 0;
}

/*
 * calls ttyname and truncates the /dev/ part if any
 */
char *whats_my_line(int fd){
	char *rv;
	if (rv = ttyname(0)) /* if nonull trim off /dev prefix */
		if (strncmp(rv, "/dev/", 5) == 0)
			rv += 5;
	return rv;
}
/*
 *	show_info(): Display the contents of the utmp struct
 *	in human readable form
 *	* displays nothing if record has no user name
 */
void show_info(struct utmp *utbufp)
{
	if (utbufp->ut_type != USER_PROCESS )
		return ;
	printf("%-8.8s", utbufp->ut_name); /* the login name */
	printf(" ");
	printf("%-8.8s", utbufp->ut_line); /*the tty */
	printf(" ");
	showtime(utbufp->ut_tv.tv_sec);
#ifdef SHOWHOST
	if (utbufp->ut_host[0] != '\0')
		printf(" (%s)",utbufp->ut_host);
#endif
	printf("\n");
}
void showtime(long timeval){

	char *cp;

	cp  = ctime(&timeval);

	printf("%12.12s",cp+4);


}

