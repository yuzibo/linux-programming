#!/usr/bin/python
# -*- coding: UTF-8 -*-

"""
这是一个二维子类的练习
When you do the addition Python evaluates it from left to right
so it is interpreted as:

((v1+v2) + v3)

so Python does:

v1.__add__(v2)
Which returns a new vector, let's call it vt

Python then does:

vt.__add__(v3)

which returns another new vector, lets call it result,
which is what gets printed using

print (result.__str__())

"""

class Vector:
	def __init__(self, a, b):
		self.a = a
		self.b = b

	def __str__(self):
		return 'Vector (%d %d)' % (self.a, self.b)

	def __add__(self, other):
		return Vector(self.a + other.a, self.b + other.b)

V1 = Vector(2,10)
V2 = Vector(5, -2)
V3 = Vector(16, -14)

print(V1 + V2 + V3)
