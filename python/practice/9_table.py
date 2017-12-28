#!/usr/bin/python
# -*- coding: UTF-8 -*-
'''
输出 9*9 乘法口诀表
关键要注意","的使用，不太一样
'''
for i in range(1, 10):
	print
	for j in range(1, i + 1):
		print "%d * %d = %d  " % (i, j, i*j),
