#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: mpl_squares.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月27日 星期一 21时51分39秒

import matplotlib.pyplot as plt
import matplotlib

zhfont1 = matplotlib.font_manager.FontProperties(fname='/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc')

x_values = list(range(1, 1001))
y_values = [x**2 for x in x_values]
"""
plt.scatter(x_values, y_values,  edgecolor = 'none', c = y_values, s=40)

plt.title(u"平方数", fontsize = 24, fontproperties = zhfont1)

plt.xlabel(u"值", fontsize = 24, fontproperties = zhfont1)

plt.ylabel(u"值的平方",  fontsize = 24, fontproperties = zhfont1)

plt.axis([0, 1100, 0, 1100000])

# 标记大小
plt.tick_params(axis = "both", which = 'major', labelsize = 14)

#plt.show()
plt.savefig('squares_plot.png', bbox_inches = 'tight')
"""
from random import choice

class RandomWalk():
    def __init__(self, num_point = 5000):
        """ 初始化随机漫步的属性"""
        self.num_point = num_point

        # 所有的随机漫步都始于(0,0)
        self.x_values = [0]
        self.y_values = [0]


    def fill_walk(self):
    # walk and up to length of
        while len(self.x_values) < self.num_point:
        # decise direction and distance
            x_direction = choice([-1, 1])
            x_distance = choice([0, 1, 2, 3, 4])
            x_step = x_direction * x_distance

            y_direction = choice([-1, 1])
            y_distance = choice([0, 1, 2,3,4])
            y_step = y_direction * y_distance

        # refuse keep original
            if x_step == 0 and y_step == 0:
                continue

        # caluate next x and y, x_step add last element in x_values
            next_x = self.x_values[-1] + x_step
            next_y = self.y_values[-1] + y_step

            self.x_values.append(next_x)
            self.y_values.append(next_y)
