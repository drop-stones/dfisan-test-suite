import argparse
from time_stat import exec_time_command_with_asan
from print_stat import print_all

spec_list = [
  "401.bzip2",
  "429.mcf",
  "433.milc",
  "445.gobmk",
  "456.hmmer",
  "458.sjeng",
  "462.libquantum",
  "464.h264ref",
  "470.lbm"
]

output_list = []
for spec in spec_list:
  output_list.append(spec + '.txt')

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description = 'run sample apps')
  parser.add_argument('-n', dest='num', type=int)
  parser.add_argument('-o', dest='output', type=str)
  parser.add_argument('--spec', type=str)
  parser.add_argument('--all', action='store_const', const=True, default=False)
  parser.add_argument('--result', action='store_const', const=True, default=False)
  args = parser.parse_args()

  if args.all:
    if args.num is None:
      parser.print_help()
      exit(1)

    for spec in spec_list:
      command = 'lit . -q --filter=' + spec 
      output = spec + '.txt'
      exec_time_command_with_asan(args.num, output, command)

  elif args.spec:
    if args.num is None or args.spec is None:
      parser.print_help()
      exit(1)

    command = 'lit . -q --filter=' + args.spec
    exec_time_command_with_asan(args.num, args.output, command)

  if args.result:
    print_all(output_list)
