#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: bst.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年12月22日 星期五 09时25分39秒

import sys, time

gk = lambda i,j:str(i)+',' + str(j)

# p 是关键字的概率(n个)，ｑ是伪关键字的概率，ｎ是关键字的个数
# 设置最大值，取出p和q中的最大的一个概率值，乘以n+1(深度)，　共有
# len(p) + len(q)个结点，
def optimal_BST(p, q, n):
    MAX = (max(p) > max(q) and max(p) or max(q))*(n + 1)*(len(p)+len(q))


#定义三个集合
#e存放期望，w存放概率和，root存放子树的根节点
    e, w, root = {}, {}, {}
    for i in xrange(1, n + 2):
        e[gk(i, i - 1)] = q[i - 1]
        w[gk(i, i - 1)] = q[i - 1]
    for l in xrange(1, n + 1):
        for i in xrange(1, n - l + 2):
            j = i + l - 1
            e[gk(i, j)] = MAX
            w[gk(i, j)] = w[gk(i, j - 1)] + p[j - 1] + q[j]
            for r in xrange(i, j + 1):
                t = e[gk(i, r - 1)] + e[gk(r+1,j)] + w[gk(i, j)]
                if t < e[gk(i, j)]:
                    e[gk(i, j)] = t
                    root[(gk(i,j))] = r
    return e, root

# p 是关键字的概率(n个)，ｑ是伪关键字的概率，ｎ是关键字的个数
def main():
    p = [0.15, 0.10, 0.05, 0.10, 0.20]
    q = [0.05, 0.10, 0.05, 0.05, 0.05, 0.10]
    e, root = optimal_BST(p, q, len(p))
    print e[gk(1, len(p))]

if __name__ == '__main__':
    main()
