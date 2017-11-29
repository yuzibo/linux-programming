#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: die.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月29日 星期三 16时02分56秒

from random import randint

class Die():
    """ a class of die(骰子)"""
    def __init__(self, num_sides = 6):
        # default a die have 6 sides
        self.num_sides = num_sides

    def roll(self):
        """ return a random number between 1 and side"""
        return randint(1, self.num_sides)




