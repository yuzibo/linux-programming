/*
 *
 *     File Name: utmplib.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年06月30日 星期四 04时29分26秒
 */
/**
 * utmplib.c - functions to buffer reads from utmp file
 * the file should incorpate with who3.c together
 *
 */
#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<sys/types.h>

#define NRECS	16
#define NULLUT	((struct utmp *)NULL)
#define UTSIZE	(sizeof(struct utmp))
static char utmpbuf[NRECS * UTSIZE]; /* storage */
static int num_recs;			/* num stored */
static int cur_rec;			/* next to go */
static int fd_utmp = -1;		/* read from */

utmp_open(char *filename){
	fd_utmp = open(filename, O_RDONLY);
	cur_rec = num_recs = 0;	/* no recs yet */
	return fd_utmp;
}
struct utmp *utmp_next() /* return pointer to next struct */
{
	struct utmp *recp;
	if(fd_utmp == -1)
		return NULLUT;
	if(cur_rec == num_recs && utmp_reload() == 0)
		return NULLUT;
	/* get address of next record */
	recp = (struct utmp *) &utmpbuf[cur_rec * UTSIZE];
	cur_rec++;
	return recp;
}

/*read next bunch of records into buffer */
int utmp_reload()
{
	int amt_read;
	/* read them in */
	amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
	/* how many did we get ?*/
	num_recs = amt_read/UTSIZE;

	cur_rec = 0;
	return num_recs;
}
utmp_close(){
	if(fd_utmp != -1)
		close(fd_utmp);

}
