import argparse
import os
from print_stat import calc_time_and_memory

spec_list = [
  '401.bzip2',
  '429.mcf',
  '433.milc',
  '445.gobmk',
  '456.hmmer',
  '458.sjeng',
  '462.libquantum',
  '464.h264ref',
  '470.lbm'
]

# comp_list1 = []
# comp_list2 = []

def calc_overhead(base: float, comp: float) -> float:
  if base == 0:
    return 0
  return ((comp / base) - 1) * 100

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('dir1')
  parser.add_argument('dir2')
  args = parser.parse_args()
  print('Dir1: ' + args.dir1)
  print('Dir2: ' + args.dir2)

  dir1_path = os.path.join(os.getcwd(), args.dir1)
  dir2_path = os.path.join(os.getcwd(), args.dir2)

  for spec in spec_list:
    # comp_list1.append(os.path.join(dir1_path, spec + '.txt'))
    # comp_list2.append(os.path.join(dir2_path, spec + '.txt'))
    res1 = os.path.join(dir1_path, spec + '.txt')
    res2 = os.path.join(dir2_path, spec + '.txt')

    time1, mem1 = calc_time_and_memory(res1)
    time2, mem2 = calc_time_and_memory(res2)

    print(spec)
    # print('Base Time(s): ' + time1 + ',\tMem(kBytes): ' + mem1)
    # print('Comp Time(s): ' + time2 + '(+' + str(calc_overhead(time1, time2)) + '%),\tMem(kBytes): ' + mem2 + '(+' + str(calc_overhead(mem1, mem2)) + '%)')
    print(f'Base Time(s): {time1:.2f},\tMem(kBytes): {mem1:.2f}')
    print(f'Comp Time(s): {time2:.2f}(+{calc_overhead(time1, time2):.2f}%), Mem(kBytes): {mem2:.2f}(+{calc_overhead(mem1, mem2):.2f}%)')
