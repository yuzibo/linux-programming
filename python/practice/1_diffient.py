#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 四个数字1,2,3,4能够组成多少不同的且无重复的三位数
'''
注意如何是添加到列表中，l.append（）方法只可以有一个参数，
所以，将列表[]作为一个参数即可
'''
l = []
for i in range(1, 5):
	for j in range(1, 5):
		for k in range(1, 5):
			if (i != j) and (j != k) and (i != k):
				l.append([i, j,k])

print("%d" % len(l))
print "总数量:", len(l)
print(l)

