#! /usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt

def plot_bar(data, colors, labels, margin=0.2):
  total_width = 1 - margin
  for i, h in enumerate(data):
    pos = x - total_width * ( 1 - (2*i + 1) / len(data) ) / 2
    plt.bar(pos, h, color=colors[i], label=labels[i], width = total_width/len(data))

## Spec2006
x = np.array(range(1, 10))
x_labels = [
  '401.bzip2',
  '429.mcf',
  '433.milc',
  '445.gobmk',
  '456.hmmer',
  '458.sjeng',
  '462.libquantum',
  '464.h264ref',
  '470.lbm',
]
bar_labels = [
  'asan',
  'smatus',
  'SafeFlow'
]
bar_colors = [ 'tab:green', 'tab:red', 'tab:blue' ]
asan_time_overheads = [
  70.1,
  39.2,
  35.5,
  111.3,
  90.6,
  127.4,
  76.0,
  0,
  75.1
]
smatus_time_overheads = [
  468.8,
  576.6,
  292.2,
  0,
  627.1,
  411.8,
  604.6,
  0,
  425.3
]
safeflow_time_overheads = [
  255.7,
  36.5,
  33.7,
  89.5,
  123.3,
  88.7,
  210.6,
  116.6,
  81.7
]
run_overheads = [
  asan_time_overheads,
  smatus_time_overheads,
  safeflow_time_overheads
]

fig = plt.figure(figsize=(13, 5))
plt.xlabel('Benchmark')
plt.ylabel('Runtime Overhead (%)')

plot_bar(run_overheads, bar_colors, bar_labels)

plt.text(3.875, 5, 'NaN', fontsize='small')
plt.text(7.875, 5, 'NaN', fontsize='small')
plt.text(7.65, 5, 'NaN', fontsize='small')

plt.xticks(x, x_labels)
plt.legend()
plt.savefig('spec2006_runtime_overhead.png')
plt.clf()


asan_mem_overheads = [
  9.0,
  82.9,
  325.5,
  577.2,
  528.8,
  2.5,
  23.8,
  0,
  13.3
]
smatus_mem_overheads = [
  0.2,
  5270.0,
  13.9,
  0,
  0.7,
  0.3,
  0.8,
  0,
  0.1
]
safeflow_mem_overheads = [
  8.1,
  5.5,
  14.2,
  64.0,
  1.0,
  11.2,
  0.9,
  66.0,
  3.4
]
mem_overheads = [
  asan_mem_overheads,
  smatus_mem_overheads,
  safeflow_mem_overheads
]

fig = plt.figure(figsize=(13, 5))
plt.xlabel('Benchmark')
plt.ylabel('Memory Overhead (%)')

plot_bar(mem_overheads, bar_colors, bar_labels)

plt.text(3.875, 5, 'NaN', fontsize='small')
plt.text(7.875, 5, 'NaN', fontsize='small')
plt.text(7.65, 5, 'NaN', fontsize='small')
plt.text(1.7, 605, '+5270.0')

plt.ylim(0, 600)
plt.xticks(x, x_labels)
plt.legend()
plt.savefig('spec2006_memory_overheads.png')
plt.clf()


## Phoenix sample_apps
x = np.array(range(1, 8))
x_labels = [
  'hist',
  'kmeans',
  'lreg',
  'pca',
  'reverseindex',
  'string_match',
  'word_count'
]
bar_labels = [
  'tsan',
  'SafeFlow'
]
bar_colors = [ 'tab:green', 'tab:blue' ]
tsan_time_overheads = [
  706.0,
  15214.8,
  -44.3,
  30730.0,
  278.6,
  2510.6,
  2239.7
]
safeflow_time_overheads = [
  379.7,
  150.2,
  65.8,
  100.0,
  10.9,
  99.9,
  4.4
]
time_overheads = [
  tsan_time_overheads,
  safeflow_time_overheads
]

fig = plt.figure(figsize=(9, 5))
plt.xlabel('Benchmark')
plt.ylabel('Runtime Overhead (%)')

plot_bar(time_overheads, bar_colors, bar_labels, 0.45)

plt.text(1.5, 760, '+15214.8')
plt.text(3.5, 760, '+30730.0')
plt.text(5.5, 760, '+2510.6')
plt.text(6.5, 760, '+2239.7')

plt.ylim(-50, 750)
plt.xticks(x, x_labels)
plt.legend()
plt.savefig('phoenix_runtime_overheads.png')
plt.clf()

tsan_mem_overheads = [
  203.2,
  1423.8,
  208.3,
  674.3,
  243.9,
  208.2,
  251.6
]
safeflow_mem_overheads = [
  1.1,
  478.8,
  2.8,
  146.5,
  2.1,
  2.7,
  20.1
]
mem_overheads = [
  tsan_mem_overheads,
  safeflow_mem_overheads
]

fig = plt.figure(figsize=(9, 5))
plt.xlabel('Benchmark')
plt.ylabel('Memory Overhead (%)')

plot_bar(mem_overheads, bar_colors, bar_labels, 0.45)

plt.text(1.5, 710, '+1423.8')

plt.ylim(0, 700)
plt.xticks(x, x_labels)
plt.legend()
plt.savefig('phoenix_memory_overheads.png')
plt.clf()
