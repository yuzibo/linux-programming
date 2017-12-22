/*
 *     File Name: prim.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年12月11日 星期一 20时33分32秒
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


/*
 * 默认的最大值是1000000
 * 权重为这个值，表示结点之间没有连接
 * */



/*
 *
 * store global value .
 * */
int c[10][10];

/*
 * 定义一个宏，方便打印二维数组
 *
 * */

void out_put(int c[][10], int n)
{
	int i, j;
	for(i = 1; i <= n; i++){
		printf("\n");
		for(j = 1; j <= n; j++){
			printf("%d\t", c[i][j]);
		}
	}
}


/*
 * 在快速排序算法中，为了方便使用，我将计数的N和MAX分别设置为
 * 全局变量，这里，我也将存储图的二维数组也定义为全局变量
 * */

/*
 * 按照输入文件的数据读入数，n是图的顶点数
 * 初始化为每一个结点与其他节点为不相连的，即
 * 设置为100000
 *
 * */

void initliaze(int n)
{
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j ++)
			c[i][j] = 1000000;
	}
}
void prim(int n)
{
/*
 * 参数说明: 采用全局变量的方式;
 * n 是n个节点。矩阵是代表权值。
 * */
	int i ;
	int lowcost[n + 1];

	int closet[n + 1];
	int flags[n + 1];
/*
 *  标志变量
 * */
	flags[1] = 1;
	/*
	 * 从结点１开始
	 * */

	printf("从结点1开始，则prim的路径为:\n 1\t");
	for(i = 2;i <= n; i++){
		lowcost[i]  = c[1][i];
		closet[i] = 1;
		flags[i] = 0;
	}
	for(i = 1; i < n; i++){
		int MAX_NUM = 1000000;
		int j = 1;
		int k;
		for(k = 2; k <= n; k++){
			/*
			 *  select elment from T - S,which value is minest
			 *
			 * */
			if((lowcost[k] < MAX_NUM) && (!flags[k])){
				j = k;
				MAX_NUM = lowcost[k];
			}
		}
			printf("%d\t ",j);
			flags[j] = 1;
			for(k = 2; k <= n; k++){
				/*
				 * here,search lowest value after updated.
				 * closet[j] is j conjcents S.
				 * */
				if((c[j][k] < lowcost[k]) && !flags[k]){
					lowcost[k] = c[j][k];
					closet[k] = j;
				}

			}
	}

}

/*
 * 下面的主函数中，我使用了打开文件的方法输入数据，因为对于这样的二维数组，
 * 如果采用手工的方法，则会耗费大量的精力，so, i read data from file
 * 当然，如果你不小心将prim.in这个数据文件丢失的话，那么这个文件就报错的
 */

int main()
{
	freopen("prim.in","r", stdin);
	int n;
	scanf("%d",&n);
	initliaze(n);
	int i,j;
	for(i  = 1; i <= n; i++)
		for(j = 1; j <= n; j++ )
			scanf("%d",&c[i][j]);

	out_put(c, n);
	printf("\n");
	prim(n);
	printf("\n");

}


