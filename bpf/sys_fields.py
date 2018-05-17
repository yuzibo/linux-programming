#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: sys_fields.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2018年05月17日 星期四 16时45分10秒

from bcc import BPF
prog = """
int hello(void *ctx)
{
    bpf_trace_printk("Hello, yubo\\n");
    return 0;
}
"""

# load BPF program
b = BPF(text=prog)
b.attach_kprobe(event="sys_clone", fn_name="hello")

print("%-18s %-16s %-6s %s" % ("TIME(S)", "COMM", "PID", "MESSAGE"))

while 1:
    try:
        (task, pid, cpu, flags, ts, msg) = b.trace_fields()
    except ValueError:
        continue
    print("%-18.9f %-16s %-6d %s" % (ts, task, pid, msg))

