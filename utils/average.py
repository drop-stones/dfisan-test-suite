#!/usr/bin/env python
import os.path
import json
import argparse
import compare

if __name__ == "__main__":
  parser = argparse.ArgumentParser(prog='average.py')
  parser.add_argument('-n', type=int, dest='iter_num', required=True)
  parser.add_argument('-o', type=str, dest='output_filename', required=True)
  config = parser.parse_args()

  print('Iteration num: ' + str(config.iter_num))
  print('Output filename: ' + config.output_filename)

  ### Run the test <iter_num> times
  files = []
  for i in range(config.iter_num):
    files.append(str(i) + "_" + config.output_filename)
    command = "lit . -q -o " + files[i]
    print(str(i) + ': ' + command)
    os.system(command)

  ### Read the result
  data = compare.readmulti(files)

  proggroup = data.groupby(level=1)
  size = len(proggroup.indices)
  metric = 'exec_time'

  ### Calculate sum of exec_time
  sum = [0] * size
  for i in range(config.iter_num):
    for j in range(size):
      idx = (i * size) + j
      sum[j] += data[metric][idx]

  ### Calculate average
  average = [0] * size
  for i in range(size):
    average[i] = round(sum[i] / config.iter_num, 4)

  ### Load 0_<output_filename> to get information other than execution time
  jsondata = json.load(open(files[0]))

  ### Overwrite execution time with average time
  for i in range(size):
    jsondata["tests"][i]["metrics"]["exec_time"] = average[i]
  
  ### Dump the result to <output_filename>
  with open(config.output_filename, 'w') as f:
    json.dump(jsondata, f, indent=2)

  ### Print the result
  print('')
  print('Average Time:')
  compare_command = os.path.dirname(os.path.realpath(__file__)) + '/compare.py'
  os.system(compare_command + ' ' + config.output_filename)
