/*
 *     File Name: bst.c
 *     Author: Bo Yu
 *     Mail: tsu.yubo@gmail.com
 *     Created Time: 2017年12月21日 星期四 19时43分55秒
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <iostream>
using namespace std;

#define DBL_MAX 1.7976931348623158e+308
int n = 5; /* 5个结点*/

double OPTIMAL_BST(double *p, double *q, int n, double **e, double **w, int **root)
{
	int i, j, l,r;
	for(i = 1; i <= n + 1; i++){
		e[i][i-1] = q[i-1];
		w[i][i-1] = q[i-1];
	}
	for (l = 1; l <= n; l++){
		for(i=1; i<=n-l+1; i++){
			int j=i+l-1;
			e[i][j] = DBL_MAX;
			w[i][j] = w[i][j-1]+p[j] +q[j];
			for(r = i; r <= j; r++){
				double t = e[i][r-1]+e[r+1][j] + w[i][j];
				if(t < e[i][j]){
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
	return e[1][n];
}
void construct_optimal_bst(int **root, int i, int j)
{
	if (i == 1 && j == n)
		printf("K%d为根\n", root[i][j]);
	if (i < j){
		printf("K%d是K%d的左孩子\n", root[i][root[i][j]-1], root[i][j]);
		construct_optimal_bst(root, i, root[i][j] - 1);
		if (root[i][j] + 1 < j)
			printf("K%d是K%d的右孩子\n", root[root[i][j]+1][j], root[i][j]);
		construct_optimal_bst(root, root[i][j] +1, j);
	}
	if (i ==j){
		printf("d%d是K%d的左孩子\n", i-1, i);
		printf("d%d是K%d的右孩子\n", i, i);
	}
}
int main()
{
	double p[6] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
	double q[6] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
	/* 下标范围：e[1..n+1,0..n]  w[1..n+1,0..n] root[1..n,1..n] */
	double **e=new double *[n+2];
	for(int i=0;i<=n+1;i++) e[i]=new double[n+1];
	double **w=new double *[n+2];
	for(int i=0;i<=n+1;i++) w[i]=new double[n+1];
	int **root=new int *[n+1];
	for(int i=0;i<=n;i++) root[i]=new int[n+1];
        /* 计算表e和root */
        cout<<"最优期望搜索代价："<<OPTIMAL_BST(p,q,n,e,w,root)<<endl;
        /* 打印root */
	 construct_optimal_bst(root,1,n);
	 /* 回收内存 */
	 for (int i = 0; i < n+2; i++)
	{
		 delete e[i],delete w[i];
		e[i] = NULL,w[i] = NULL;
		 if(i!=n+1)
		 {
			delete root[i];
			root[i] = NULL;
		}
	}
			delete []e,delete[]w,delete []root;
			e = NULL,w=NULL,root=NULL;
    return 0;

}
