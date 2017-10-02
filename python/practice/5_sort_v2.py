#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 字典的用法 sorted
x = int(raw_input("x:"))
y = int(raw_input("y:"))
z = int(raw_input("z:"))

a = {"x": x, "y": y, "z": z}
for w in sorted(a, key=a.get):
	print w, a[w]

