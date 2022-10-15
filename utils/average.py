#!/usr/bin/env python
import pandas as pd
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
    # os.system(command)

  ### Read json files
  json_data = compare.readmulti(files)

  ### Collect test names
  testnames = set()
  for testname in json_data.index.get_level_values('Program'):
    testnames.add(testname)

  ### Slice and calculate sum of exec_time
  sum = {}
  for testname in testnames:
    sum[testname] = 0

  for testname in testnames:
    testdata = json_data.loc[pd.IndexSlice[:, testname], :]
    for exec_time in testdata['exec_time']:
      sum[testname] += exec_time
  
  ### Calculate average of exec_time
  average = {}
  for testname, sum_exec_time in sum.items():
    average[testname] = round(sum[testname] / config.iter_num, 4)
  
  with open(files[0], 'r') as f:
    result = json.load(f)
  
  for test in result['tests']:
    if test.get('name') == None or test.get('metrics') == None:
      continue
    test['metrics']['exec_time'] = average[test['name']]

  ### Dump the result to <output_filename>
  with open(config.output_filename, 'w') as f:
    json.dump(result, f, indent=2)

  ### Print the result
  print('')
  print('Average Time:')
  compare_command = 'python3 ' + os.path.dirname(os.path.realpath(__file__)) + '/compare.py'
  os.system(compare_command + ' ' + config.output_filename)
