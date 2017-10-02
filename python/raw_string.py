#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 这个文件可以将``` ***```中的内容输出到屏幕

import sys

lines = r'''

for line in range(5):
	print('Hello\tWorld')
'''

print(lines.strip())

sys.stdout.write(lines.strip())
sys.stdout.write('\n')
