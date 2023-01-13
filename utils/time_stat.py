import os

def exec_time_command(iter_num: int, output: str, exe_command: str):
  rm_command = 'rm -f ' + output
  print(rm_command)
  os.system(rm_command)

  command = 'time -p -v -o ' + output + ' -a ' + exe_command
  for i in range(iter_num):
    print(command)
    os.system(command)

def exec_time_command_with_asan(iter_num: int, output: str, exe_command: str):
  rm_command = 'rm -f ' + output
  print(rm_command)
  os.system(rm_command)

  command = 'ASAN_OPTIONS=detect_leaks=0 time -p -v -o ' + output + ' -a ' + exe_command
  for i in range(iter_num):
    print(command)
    os.system(command)
