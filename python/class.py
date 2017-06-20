#!/usr/bin/python3
# -*- coding: UTF-8 -*-
'''
这段代码简单的介绍了class的用法，注意他的继承，每个类里面的方法，有默认的
@	__init__ 参数，下面进行赋值
@	__str__ 格式化字符串

需要注意class Developer
这里可以直接继承 Employee 的__STR__

需要使用v3

'''
from __future__ import print_function

class Employee:
	"""Class with FirstName, LastName, Salary"""
	def __init__(self, FirstName, LastName, Salary):
		self.FirstName = FirstName
		self.LastName = LastName
		self.Salary = Salary
	def __str__(self):
		return '("{}" "{}" "{}")'.format(self.FirstName,
self.LastName, self.Salary)

class Developer(Employee):
	"""define a subclass, augment with ProgLang"""

	def __init__(self, FirstName, LastName, Salary, ProgLang):
		Employee.__init__(self, FirstName, LastName, Salary)
		self.ProgLang = ProgLang

	def dev_repr(self):
		return '("{}" "{}" "{}" "{}")'.format(self.FirstName,
self.LastName, self.Salary, self.ProgLang)


	def __str__(self):
		sup = super().__str__()
		return ' "{}")'.format(sup, self.ProgLang)

a = Employee("Bo", "YU", 89000)
print(a)

dev_1 = Developer("Chun", "HE", "63000", "C")
print(dev_1)
print(dev_1.dev_repr())


