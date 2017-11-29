#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: rw_visual.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月29日 星期三 09时46分20秒

import matplotlib.pyplot as plt

from mpl_squares import RandomWalk

# 创建一个RandomWalk（）实例
while True:

    rw = RandomWalk()
    rw.fill_walk()

    point_numbers = list(range(rw.num_point))
    plt.scatter(rw.x_values, rw.y_values, c=point_numbers, cmap=plt.cm.Blues,edgecolor='none', s=15)


    plt.scatter(0,0,c='green', edgecolor='none', s=100)
    plt.scatter(rw.x_values[-1], rw.y_values[-1], c='red', edgecolor='none', s=15)

    # hint axes()
    plt.axes().get_xaxis().set_visible(False)
    plt.axes().get_yaxis().set_visible(False)

    plt.show()

    keep_running = raw_input("Make a another walk(Y/N)?")
    if keep_running == 'N' or 'n':
        break
