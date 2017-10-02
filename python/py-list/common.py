#!/usr/bin/python
# -*- coding: UTF-8 -*-
"""
从这个python源代码读到的东西有很多：
1. import 相关的模块
import sys, collections
然后这么使用： collections.Counter() -> from collections import Counter
但是我感觉这一点不容易察觉哪个函数来自于哪个模块
2，给函数传递参数使用常量
def find_common_words(textfile, top = 10): -> DEFAULT_TOP_SIZE = 10
3. 参数名字的取值应该望字知意
def find_common_words(textfile, DEFAULT_TOP_SIZE): -> textfile >> textname
4.
    textfile = open(filename)
    text = textfile.read().lower()
    textfile.close() ->

    with open(filename) as textfile:  这样自动关闭了文件。即便发生了意外，也没有问题
5. text = textfile.read().lower()
这样读取了整个文件，不应该 ->
"""
from collections import Counter
import sys

DEFAULT_TOP_SIZE = 10

def find_common_words(filename, DEFAULT_TOP_SIZE):
    ''' return the most common words in the textfile, that use dict with counter 合理 '''

    with open(filename) as textfile:
        C = Counter()
        for line in textfile:
            words = line.lower().split()
            C.update(words)

    return dict(C.most_common(DEFAULT_TOP_SIZE))

filename = sys.argv[1]
top_five_words = find_common_words(filename, 5)
print (top_five_words)


"""
源代码：
import sysimport collections
def find_most_common_words(textfile, top=10):
        ''' Returns the most common words in the textfile.'''

            textfile = open(textfile)
            text = textfile.read().lower()
            textfile.close()
            words = collections.Counter(text.split()) # how often each word appears

            return dict(words.most_common(top))

filename = sys.argv[1]
top_five_words = find_most_common_words(filename, 5)
"""
