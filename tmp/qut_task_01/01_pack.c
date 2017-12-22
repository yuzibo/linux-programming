/*
 *     File Name: 01_pack.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年12月22日 星期五 15时29分51秒
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_NUM 10000

/*
 * 物品个数，　背包容量，　最大价值
 * */
int	cap = 25;
int	num = 3;
int	w[num] = {20, 15, 10};
int	p[num] = {20, 30, 25};

/**
 * 　物品的价值　物品的重量　x[i]标记物品的选中与否　
 */
//#int p[MAX_NUM], w[MAX_NUM], x[MAX_NUM], max_x[MAX_NUM];


/*
 * cw当前包内物品重量，cp当前包内物品价值
 */
void backtrack(int i, int cp, int cw)
{
	int j;
	if (i > num){
		if(cp > max_value){
			max_value = cp;
			for (i = 0; i<= num; i++)
				max_x[i] = x[i];
		}
	} else
		for(j = 0; j <= 1; j++){
			x[i] = j;
			if (cw+x[i]*w[i] <= cap){
				cw += w[i] * x[i];
				cp += p[i] * x[i];
				backtrack( i + 1, cp, cw);
				cw -= w[i] * x[i];
				cp -= p[i] * x[i];
			}
		}
}

int main()
{
	int i;
	max_value = 0;
	backtrack(1,0,0);
	printf("最大价值为:\n");
	printf("%d\n", max_value);
	printf("被选中的物品依次是：\n");
	for (i = 1; i <= num ;i++){
		printf("%d", max_x[i]);
		printf("\n");
	}
}
