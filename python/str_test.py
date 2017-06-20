#!/usr/bin/python
# -*- coding: UTF-8 -*-


# 17-06-20-p1_2
# Repalced quote() with repr()
# what is inspect

import inspect

class Employee:
	'''Class with FirstName, Lastname, Salary'''
	def __init__(self, FirstName, Lastname, Salary):
		self.FirstName = FirstName
		self.Lastname = Lastname
		self.Salary = Salary

	def __str__(self):
		names = inspect.getargspec(self.__init__).args[1:]
		values = (getattr(self, name) for name in names)
		return "({})".format(" ".join(map(repr, values)))

class Developer(Employee):
	"""Define a subclass, augment with Proglang"""
	def __init__(self, FirstName, Lastname, Salary, Proglang):
		super().__init__(FirstName, Lastname, Salary)
		self.Proglang = Proglang


a = Employee("Bo", "YU", 89098)
print(a)

b = Developer("CHUN", "He", 98889, "PYTHON")

print(b)
