/*
 *     File Name: 01_2.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年12月28日 星期四 06时15分34秒
 */
#include <stdio.h>

#define max 100

/* 保存物体的重量 */
int weight[max];

/* 保存物体的价值*/
int value[max];

/* 物品数量， 当前最大的重量， 当前最大价值 */
int n, max_weight, max_value;

int best_answer[max], answer[max];

void print()
{
	int i, j,k,l;
	printf("The max value is %d\n,这个可行解是\n", max_value);

	for (i = 1; i<= n ;i++){
		printf("%d\t", best_answer[i]);

	}
	printf("\n");

}
void knapsack_back(int level, int current_weight, int current_value)
{
	if(level >= n+1){
		if (current_value > max_value){
			int i;
			max_value = current_value;
			for(i = 1; i <= n; i++){
				best_answer[i] = answer[i];
			}
		}
	}
	else{
		if(current_weight >= weight[level + 1]){
			current_weight = current_weight - weight[level + 1];
			current_value = current_value + value[level + 1];
			answer[level + 1] = 1;
			knapsack_back(level+1, current_weight, current_value);
			answer[level+1] = 0;
			current_weight = current_weight + weight[level + 1];
			current_value = current_value - value[level + 1];
		}
		knapsack_back(level+1, current_weight, current_value);
	}
}

/* 将所有的路径填充为0 */
void init()
{
	int i;
	max_value = 0;
	for(i = 1; i<=n; i++){
		answer[i] = 0;
	}
}
void input()
{
	int i,j;
	scanf("%d%d", &n, &max_weight) ;
		for(i = 1; i<=n; i++)
			scanf("%d", &weight[i]);
		for (j = 1; j <= n; j++)
			scanf("%d", &value[j]);
		
}
int main()
{
	input();	
	init();
	knapsack_back(0, max_weight, 0);
	print();
	
	return 0;
}
