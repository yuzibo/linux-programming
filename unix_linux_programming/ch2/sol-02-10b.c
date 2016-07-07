/*
 *     File Name: sol-02-10b.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2016年07月07日 星期四 05时24分25秒
 */
#include<stdio.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/types.h>

int main()
{
	uid_t	id; /* effective user if of process */
	struct passwd *p; /* will hold pwd data for user */
	id = geteuid();  /* manpage says geteuid always succeeds */
	p = getpwuid(id); /* get userdb info about this uid */

	if (p == NULL){
		printf("I dont't know who you are.\n");
	}
	else
		printf("%s\n",p->pw_name);
}
