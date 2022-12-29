#! /usr/bin/env python
import subprocess
import sys
import timeit
import matplotlib.pyplot as plt

times = 1 # 5

execs = ["find_max", "dfisan_find_max", "asan_find_max"]

sensitive_ratio = list(range(0, 110, 10))   # 0,10,..100
runtimes = {}
overheads = {}

def calc_overhead(exe: str):
  overheads[exe] = []
  for i in sensitive_ratio:
    overheads[exe].append(runtimes[exe][i] / runtimes["find_max"][i])

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

plt.plot(sensitive_ratio, overheads["dfisan_find_max"], label="dfisan", marker='o')
plt.plot(sensitive_ratio, overheads["asan_find_max"], label="asan", marker='x')
# plt.plot(sensitive_ratio, overheads["datashield_find_max"], label="DataShield", marker="v")

plt.xlabel('sensitive ratio')
plt.ylabel('overhead')
plt.title('find max')

plt.legend()

plt.show()
