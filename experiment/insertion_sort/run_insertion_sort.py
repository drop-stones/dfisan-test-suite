#! /usr/bin/env python
import subprocess
import sys
import timeit
import matplotlib.pyplot as plt

times = 1 # 5

execs = ["insertion_sort", "dfisan_insertion_sort", "asan_insertion_sort"]

sensitive_ratio = list(range(0, 110, 10))   # 0,10,..100
runtimes = {}
overheads = {}

def calc_overhead(exe: str):
  overheads[exe] = []
  for i in sensitive_ratio:
    overheads[exe].append(runtimes[exe][i] / runtimes["insertion_sort"][i])

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

plt.plot(sensitive_ratio, overheads["dfisan_insertion_sort"], label="dfisan", marker='o')
plt.plot(sensitive_ratio, overheads["asan_insertion_sort"], label="asan", marker='x')
# plt.plot(sensitive_ratio, overheads["datashield_insertion_sort"], label="DataShield", marker="v")

plt.xlim(1.0,2.2)

plt.xlabel('sensitive ratio')
plt.ylabel('overhead')
plt.title('insertion sort')

plt.legend()

plt.show()
