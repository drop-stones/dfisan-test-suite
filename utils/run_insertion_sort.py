#! /usr/bin/env python
import os
import argparse
import matplotlib.pyplot as plt
from time_stat import exec_time_command
from print_stat import calc_time_and_memory

execs = [
  'insertion_sort',
  'dfisan_insertion_sort',
  'dfisan_no_check_unsafe_access_insertion_sort',
  'asan_insertion_sort',
  'smatus_insertion_sort']
dir_path = 'experiment/insertion_sort/'

sensitive_ratio = list(range(0, 110, 10))   # 0,10,..100
runtimes = {}
mem_usages = {}
runtime_overheads = {}
mem_usage_overheads = {}

def calc_overhead(exe: str, base: str):
  runtime_overheads[exe] = []
  mem_usage_overheads[exe] = []
  for i in sensitive_ratio:
    runtime_overheads[exe].append(runtimes[exe][i] / runtimes[base][i])
    mem_usage_overheads[exe].append(mem_usages[exe][i] / mem_usages[base][i])

def plot_runtimes():
  plt.figure(figsize=(6,4))
  plt.plot(sensitive_ratio, runtime_overheads['dfisan_insertion_sort'], label='SafeFlow', marker='o')
  # plt.plot(sensitive_ratio, runtime_overheads['dfisan_no_check_unsafe_access_insertion_sort'], label='no unsafe check', marker='v')
  plt.plot(sensitive_ratio, runtime_overheads['asan_insertion_sort'], label='asan', color='tab:green', marker='x')
  plt.plot(sensitive_ratio, runtime_overheads['smatus_insertion_sort'], label='smatus', color='tab:red', marker='^')
  # plt.plot(sensitive_ratio, runtime_overheads['datashield_insertion_sort'], label='DataShield', marker='v')

  plt.xlabel('Sensitive Ratio (%)')
  plt.ylabel('Runtime Overhead')
  # plt.title('Insertion Sort')
  plt.ylim(1,5.2)

  plt.legend()
  # plt.show()
  plt.savefig('insertion_sort.png')

def plot():
  # plt.rcParams["font.size"] = 10
  plt.rcParams["font.size"] = 12
  fig = plt.figure()
  runtime_plot = fig.add_subplot(2, 1, 1)
  mem_plot = fig.add_subplot(2, 1, 2)

  runtime_plot.plot(sensitive_ratio, runtime_overheads['dfisan_insertion_sort'], label='SafeFlow', marker='o')
  runtime_plot.plot(sensitive_ratio, runtime_overheads['dfisan_no_check_unsafe_access_insertion_sort'], label='no unsafe check', marker='v')
  runtime_plot.plot(sensitive_ratio, runtime_overheads['asan_insertion_sort'], label='asan', marker='x')
  runtime_plot.plot(sensitive_ratio, runtime_overheads['smatus_insertion_sort'], label='smatus', marker='^')
  # runtime_plot.set_xlabel('Sensitive Ratio')
  runtime_plot.set_ylabel('Runtime Overhead')

  mem_plot.plot(sensitive_ratio, mem_usage_overheads['dfisan_insertion_sort'], label='SafeFlow', marker='o')
  mem_plot.plot(sensitive_ratio, mem_usage_overheads['dfisan_no_check_unsafe_access_insertion_sort'], label='no unsafe check', marker='v')
  mem_plot.plot(sensitive_ratio, mem_usage_overheads['asan_insertion_sort'], label='asan', marker='x')
  mem_plot.plot(sensitive_ratio, mem_usage_overheads['smatus_insertion_sort'], label='smatus', marker='^')
  mem_plot.set_xlabel('Sensitive Ratio')
  mem_plot.set_ylabel('Memory Overhead')

  runtime_plot.legend()
  # mem_plot.legend()
  # plt.show()
  plt.savefig('insertion_sort.png')

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('-n', dest='num', type=int)
  # parser.add_argument('--run', action='store_const', const=True, default=False)
  args = parser.parse_args()

  for exe in execs:
    runtimes[exe] = {}
    mem_usages[exe] = {}
    for i in sensitive_ratio:
      command = os.path.join(dir_path, exe) + ' ' + str(i)
      output_file = exe + str(i) + '.txt'
      print(command)
      if args.num:
        exec_time_command(args.num, output_file, command)
      ave_time, ave_mem = calc_time_and_memory(output_file)
      print('Ave.time: ' + str(ave_time))
      print('Ave.mem : ' + str(ave_mem))
      runtimes[exe][i] = ave_time
      mem_usages[exe][i] = ave_mem

  for exe in execs[1:]:
    calc_overhead(exe, 'insertion_sort')

  # plot_runtimes()
  plot()
