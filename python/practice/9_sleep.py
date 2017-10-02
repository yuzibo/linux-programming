#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 字典输出key和value的方法

import time

my_dict = {1: 'a', 2 : 'b', 3: 'c', 4 : 'd'}
for key, value in dict.items(my_dict):
	print key, value
	time.sleep(2)
