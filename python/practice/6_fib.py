#!/usr/bin/python
# -*- coding: UTF-8 -*-
# ???
l = []

def fib(n):
	a, b = 1, 1
	for i in range(n - 1):
		a, b = b, a+b
		l.append([a,b])

	return b

print(l)
print fib(10)
