#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: die_visual.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月29日 星期三 16时10分30秒

''' 同时投两个骰子'''

from die import Die

import pygal

die_1 = Die()
die_2 = Die()
# throw die, result in a list
results = []

for roll_num in range(1000):
    result = die_1.roll() + die_2.roll()
    results.append(result)

two_dice_sum = die_1.num_sides + die_2.num_sides

# 分析结果
frequencier = []
for value in range(1, two_dice_sum + 1 ):
    frequency = results.count(value)
    frequencier.append(frequency)

# 绘制直方图

hist = pygal.Bar()
hist.title = u"投掷1000次的结果"
hist.x_labels = ['1','2','3','4','5','6', '7','8','9','10','11','12']
hist.x_title = u"结果"
hist.y_title = u"结果的频率"

hist.add('D6 + D6\'', frequencier)
hist.render_to_file('die_visual.svg')

