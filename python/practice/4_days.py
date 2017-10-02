#!/usr/bin/python
# -*- coding: UTF-8 -*-
'''
求天数的，简单，自己写的
'''
year = int(raw_input('year:\n'))
month = int(raw_input('month(1-12):\n'))
day = int(raw_input('day(1-31):\n'))

dayes = 0
monthes = [31, 28, 31, 30,31, 30, 31, 31,30,31, 30,31]

if (year % 100 != 0 and year % 4 == 0) or (year % 100 == 0 and year % 400 == 0):
	for i in range(1, month):
		dayes += monthes[i]

	dayes += 1
else:
	for j in range(1, month):
		dayes += monthes[j]

print("第 %d 天\n: " %  (dayes + day + 1))
