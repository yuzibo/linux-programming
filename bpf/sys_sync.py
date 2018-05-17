#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: sys_sync.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2018年05月17日 星期四 15时04分58秒
from bcc import BPF

BPF(text='''
int kprobe__sys_sync(void *ctx)
{ bpf_trace_printk("Hello, yubo\\n");
return 0;}'''
).trace_print()

