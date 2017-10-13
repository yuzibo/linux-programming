/*
 *     File Name: ping.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年10月10日 星期二 16时53分33秒
 *     用于实现ping的原理
 */
#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>
#include <signal.h>


#define MAX_WAIT_TIME	5
#define MAX_NO_PACKETS 3
#define PACKET_SIZE	4096
char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];



int sockfd, datalen = 56;
struct sockaddr_in dest_addr;
pid_t pid;
int nsend = 0, nreceive = 0;

struct sockaddr_in from;
struct timeval tvrecv;

/* 校验和算法 */
unsigned short cal_chksum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;
	/* 将 ICMP报头二进制为单位累加起来 */
	while(nleft > 1){
		sum += *w++;
		nleft -= 2;
	}
	/* 这个校验和算法真的不明白 */
	if (nleft == 1){
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum&0xffff);
	sum += (sum >> 16);
	answer =~ sum;
	return answer;

}

/* 设置ICMP 报头
 * @pack_no 应该是packet seq
 * */
int pack(int pack_no)
{
	int i, packsize;
	struct icmp *icmp;
	struct timeval *tval;
	icmp = (struct icmp*)sendpacket;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = pack_no;
	icmp->icmp_id = pid;
	packsize = 8 + datalen;
	tval = (struct timeval *)icmp->icmp_data;
	gettimeofday(tval, NULL); /*记录发送时间*/
	/* 校验算法 */
	icmp->icmp_cksum = cal_chksum((unsigned short *)icmp, packsize);
	return packsize;


}

/* 发送三个ICMP报文 */
void send_packet()
{
	int packetsize;
	while (nsend < MAX_NO_PACKETS){
		nsend++;
		/* 设置ICMP报头 */
		packetsize = pack(nsend);
		if(sendto(sockfd, sendpacket, packetsize, 0,
			(struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
		{
			perror("sendto error");
			continue;
		}
		sleep(1); /*每隔一秒发送一个ICMP报文*/
	}

}
/* 统计信息*/
void statistics(int signo)
{
	printf("\n--------PING statistics----------\n");
	printf("%d packets transmitted, %d received, %%%d lost\n",
			nsend, nreceive, (nsend - nreceive)/nsend * 100);
	close(sockfd);
	exit(1);


}
/*两个timeval 结构相减*/
void tv_sub(struct timeval *out, struct timeval *in)
{
	if((out->tv_usec -= in->tv_usec) < 0)
	{
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

/* 剥去ICMP报头，这是理解ip结构的精彩一步 */
int unpack(char *buf, int len)
{
	int i, iphdrlen;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	double rtt;
	ip = (struct ip *)buf;
	/* 求ip报头长度，用ip报头长度标志乘以4*/
	iphdrlen = ip->ip_hl << 2;
	/* 越过ip报头，指向ICMP报头*/
	icmp = (struct icmp *)(buf + iphdrlen);
	/* * ICMP 报头及ICMP数据报的总长度*/
	len -= iphdrlen;
	/*小于 * ICMp报头长度不合理*/
	if(len < 8) {
		perror("ICMP packets\'s length is less than 8");
		return -1;
	}
	/*确保所接受的是我所发的ICMP的回应*/
	if((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid))
	{
		tvsend = (struct timeval *)icmp->icmp_data;
		/* 接受和发送时间差*
		 */
		tv_sub(&tvrecv, tvsend);
		/*以毫秒为单位计算rtt*/
		rtt = tvrecv.tv_sec * 1000 + tvrecv.tv_usec/1000;
		/*显示相关信息*/
		printf("%d bytes from %s: icmp_seq=%u ttl=%d rtt=%.3f ms\n", len, inet_ntoa(from.sin_addr), icmp->icmp_seq, ip->ip_ttl, rtt);
	}
	else
		return -1;
}
/*接受所有的
 * ICMP报文 */
void recv_packet()
{
	int n, fromlen;
	extern int errno;
	/* 调用 statistics 函数*/
	signal(SIGALRM, statistics);
	fromlen = sizeof(from);
	while(nreceive < nsend){
		alarm(MAX_WAIT_TIME);
		if((n = recvfrom(sockfd, recvpacket, sizeof(recvpacket),
				0, (struct sockaddr *)&from, &fromlen)) < 0)
		{
			if(errno == EINTR)
				continue;
			perror("recvfrom error");
				continue;
		}
		gettimeofday(&tvrecv, NULL);
		if(unpack(recvpacket, n) == -1)
			continue;
		nreceive++;

	}

}
int main(int argc, char **argv)
{
	struct hostent *host;
	struct protoent *protocol;
	unsigned long inaddr = 0l;
	int waittime = MAX_WAIT_TIME;
	int size = 50*1024;

	if(argc < 2)
	{
		printf("usage: %s hostname/IP address\n", argv[0]);
		exit(1);
	}
	if((protocol = getprotobyname("icmp")) == NULL)
	{
		perror("getprotobyname");
		exit(1);
	}
	if((sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0)
	{
		perror("socket error");
		exit(1);
	}
	/* 回收root权限，设置当前权限 */
	setuid(getuid());
	/* 扩大套接字接收缓冲区到50K,不过，对于，下面的参数我是很不了解 */
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)); bzero(&dest_addr, sizeof(dest_addr)); dest_addr.sin_family = AF_INET;
	/* 判断是主机名还是ip地址 */
	if((inaddr = inet_addr(argv[1])) == INADDR_NONE)
	{
		if((host = gethostbyname(argv[1])) == NULL) /*是主机名*/
		{
			perror("gethostbyname error");
			exit(1);
		}
		memcpy((char *)&dest_addr.sin_addr, host->h_addr, host->h_length);

	}
	else /*  是ip地址 */
	{

		printf("Here is wrong?:%s\n", argv[1]);
		memcpy((char *)&dest_addr.sin_addr, (char *)&inaddr, sizeof(argv[1]));
	}

	/* 获取main的进程id，用于设置ICMP的标识符 */
	pid = getpid();
	printf("PING %s(%s): %d bytes data in ICMP packets.\n", argv[1],
			inet_ntoa(dest_addr.sin_addr), datalen);
	send_packet(); /* 发送所有ICMP报文*/
	recv_packet(); /*接受所有的ICMP报文*/
	statistics(SIGALRM); /*进行统计*/
	return 0;


}

