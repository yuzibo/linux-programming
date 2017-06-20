#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 17-06-20-p1, 与class.py 遥相互应

def quote(value):
	#
	return '"{}"'.format(value)

class Employee:
	"""class with FirstName, LastName, Salary, """
	def __init__(self, FirstName, LastName, Salary):
		self.FirstName = FirstName
		self.LastName = LastName
		self.Salary = Salary

	def as_tuple(self):
		return self.FirstName, self.LastName, self.Salary

	def __str__(self):
		strings = (quote(a) for a in self.as_tuple())
		return "({})".format(" ".join(strings))

class Developer(Employee):
	"""Define a subclass, agument with Proglang"""
	def __init__(self, FirstName, LastName, Salary, Proglang):
		super().__init__(FirstName, LastName, Salary)
		self.Proglang = Proglang

	def as_tuple(self):
		return super().as_tuple() + (self.Proglang,)

a = Employee("Bo", "YU", 678000)
print(a)

b = Developer("Chun", "HE", 780000, "C")
print(b)
