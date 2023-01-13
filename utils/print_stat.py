import re
import argparse

time_list = []
mem_list = []

def calc_time_and_memory(filename: str):
  with open(filename) as f:
    lines = f.readlines()
    s_lines = [line.strip() for line in lines]

    num_elapsed = 0
    ave_elapsed = 0
    num_max_mem = 0
    ave_max_mem = 0
    for line in s_lines:
      if "Elapsed" in line:
          # elapsed_times = re.findall("\d:\d+\.\d+", line)
          elapsed_times = re.findall("\d+", line)
          elapsed_time = float(elapsed_times[0]) * 60 + float(elapsed_times[1]) + float(elapsed_times[2]) * 0.01
          ave_elapsed += elapsed_time
          num_elapsed += 1
      if "Maximum resident set size (kbytes)" in line:
          max_mems = re.findall("\d+", line)
          max_mem = int(max_mems[0])
          ave_max_mem += max_mem
          num_max_mem += 1

  ave_elapsed = ave_elapsed / num_elapsed
  ave_max_mem = ave_max_mem / num_max_mem
  return ave_elapsed, ave_max_mem

def calc_time_and_memory_all(file_list):
  for file in file_list:
    ave_elapsed, ave_max_mem = calc_time_and_memory(file)
    time_list.append(ave_elapsed)
    mem_list.append(ave_max_mem)
  return time_list, mem_list

def print_all(file_list, comparison_num: int = 1):
  calc_time_and_memory_all(file_list)
  for i in range(len(file_list)):
    print(file_list[i])
    if i % comparison_num == 0:
      print("Elapsed time Average: " + str(time_list[i]))
    else:
        # print(str(time_list[i]) + " / " + str(time_list[int(i/3) * 3]))
        overhead = ((time_list[i]/time_list[int(i/comparison_num) * comparison_num]) - 1) * 100
        print("Elapsed time Average: " + str(time_list[i]) + " (+" + str(overhead) + "%)")
    if i % comparison_num == 0:
      print("Maximum resident Average: " + str(mem_list[i]))
    else:
        # print(str(mem_list[i]) + " / " + str(mem_list[int(i/3) * 3]))
        overhead = ((mem_list[i]/mem_list[int(i/comparison_num) * comparison_num]) - 1) * 100
        print("Maximum resident Average: " + str(mem_list[i]) + " (+" + str(overhead) + "%)")

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--filename', type=str)
  args = parser.parse_args()

  calc_time_and_memory(args.filename)
  print("Elapsed time Average: " + str(time_list[0]))
  print("Maximum resident Average: " + str(mem_list[0]))
