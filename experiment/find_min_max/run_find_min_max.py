#! /usr/bin/env python
import subprocess
import sys
import timeit
import matplotlib.pyplot as plt

times = 5

execs = [
  "find_min_max",
  "dfisan_find_min_max",
  "dfisan_no_check_unsafe_access_find_min_max",
  "tsan_find_min_max"]

sensitive_ratio = list(range(0, 110, 10))   # 0,10,..100
runtimes = {}
overheads = {}

def calc_overhead(exe: str):
  overheads[exe] = []
  for i in sensitive_ratio:
    overheads[exe].append(runtimes[exe][i] / runtimes["find_min_max"][i])

for exe in execs:
  runtimes[exe] = {}
  for i in sensitive_ratio:
    arg = str(i)
    print("./" + exe + " " + arg)
    command = ["./" + exe, arg]
    sum_time = timeit.timeit("subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)", globals=globals(), number=times)
    ave_time = sum_time / times
    print("Ave: " + str(ave_time))
    runtimes[exe][i] = ave_time

for exe in execs[1:]:
  calc_overhead(exe)

plt.plot(sensitive_ratio, overheads["dfisan_find_min_max"], label="dfisan", marker='o')
plt.plot(sensitive_ratio, overheads["dfisan_no_check_unsafe_access_find_min_max"], label="no unsafe check", marker='v')
plt.plot(sensitive_ratio, overheads["tsan_find_min_max"], label="tsan", marker='x')

plt.xlabel('sensitive ratio')
plt.ylabel('overhead')
plt.title('find min max')

plt.legend()

plt.show()
