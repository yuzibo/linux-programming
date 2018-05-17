#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: sync_timing.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2018年05月17日 星期四 19时07分40秒

from bcc import BPF

b = BPF(text="""
#include <uapi/linux/ptrace.h>
#include <linux/blkdev.h>

BPF_HASH(last);

int do_trace(struct pt_regs *ctx){
    u64 ts, *tsp, delta, key = 0;
    /* attempt to read stored timestamp */
    tsp = last.lookup(&key);
    if (tsp != 0) {
        delta = bpf_ktime_get_ns() - *tsp;
        if (delta < 1000000000) {
            bpf_trace_printk("%d\\n", delta / 1000000);
        }
        last.delete(&key);
    }
    /* update stored timestamp */
    ts = bpf_ktime_get_ns();
    last.update(&key, &ts);
    return 0;
}
""")
b.attach_kprobe(event="sys_sync", fn_name="do_trace")
print("Tracing for quick sync's ... Ctrl -c to end ")

# format output
start = 0
while 1:
    (task, pid, cpu, flags, ts, ms) = b.trace_fields()
    if start == 0:
        start = ts
    ts = ts - start
    print("At time %.2f s: multiple syncs detected, last %s ms ago " % (ts, ms))

