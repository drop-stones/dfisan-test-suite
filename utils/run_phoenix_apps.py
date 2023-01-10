import argparse
import os
from time_stat import exec_time_command
from print_stat import print_all


phoenix_sample_apps_dir = os.path.join(os.path.dirname(__file__), '../phoenix/sample_apps')
phoenix_sample_apps_dir = os.path.normpath(phoenix_sample_apps_dir)

file_list = [
  'kmeans.txt',
  'tsan_kmeans.txt',
  'dfisan_kmeans.txt',
  'pca.txt',
  'tsan_pca.txt',
  'dfisan_pca.txt',
  'string_match.txt',
  'tsan_string_match.txt',
  'dfisan_string_match.txt',
  'word_count.txt',
  'tsan_word_count.txt',
  'dfisan_word_count.txt'
]

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description = 'run sample apps')
  parser.add_argument('-n', dest='num', type=int)
  parser.add_argument('-o', dest='output', type=str)
  parser.add_argument('--command', type=str)
  parser.add_argument('--all', action='store_const', const=True, default=False)
  parser.add_argument('--result', action='store_const', const=True, default=False)
  args = parser.parse_args()

  if args.all:
    if args.num is None:
      parser.print_help()
      exit(1)

    # kmeans
    exec_time_command(args.num, 'kmeans.txt',        phoenix_sample_apps_dir + '/kmeans/kmeans-pthread -d 10 -c 10000 -p 10000 -s 10000')
    exec_time_command(args.num, 'tsan_kmeans.txt',   phoenix_sample_apps_dir + '/kmeans/tsan_kmeans_pthread -d 10 -c 10000 -p 10000 -s 10000')
    exec_time_command(args.num, 'dfisan_kmeans.txt', phoenix_sample_apps_dir + '/kmeans/dfisan_kmeans_pthread -d 10 -c 1000 -p 10000 -s 10000')

    # pca
    exec_time_command(args.num, 'pca.txt',        phoenix_sample_apps_dir + '/pca/pca-pthread -r 1000 -c 1000 -s 1000')
    exec_time_command(args.num, 'tsan_pca.txt',   phoenix_sample_apps_dir + '/pca/tsan_pca_pthread -r 1000 -c 1000 -s 1000')
    exec_time_command(args.num, 'dfisan_pca.txt', phoenix_sample_apps_dir + '/pca/dfisan_pca_pthread -r 1000 -c 1000 -s 1000')

    # string_match
    string_match_input_file = phoenix_sample_apps_dir + '/string_match/string_match_datafiles/key_file_500MB.txt'
    exec_time_command(args.num, 'string_match.txt',        phoenix_sample_apps_dir + '/string_match/string_match_pthreads '        + string_match_input_file)
    exec_time_command(args.num, 'tsan_string_match.txt',   phoenix_sample_apps_dir + '/string_match/tsan_string_match_pthreads '   + string_match_input_file)
    exec_time_command(args.num, 'dfisan_string_match.txt', phoenix_sample_apps_dir + '/string_match/dfisan_string_match_pthreads ' + string_match_input_file)

    # word_count
    word_count_input_file = phoenix_sample_apps_dir + '/word_count/word_count_datafiles/word_100MB.txt'
    exec_time_command(args.num, 'word_count.txt',        phoenix_sample_apps_dir + '/word_count/wordcount_pthreads '        + word_count_input_file)
    exec_time_command(args.num, 'tsan_word_count.txt',   phoenix_sample_apps_dir + '/word_count/tsan_wordcount_pthreads '   + word_count_input_file)
    exec_time_command(args.num, 'dfisan_word_count.txt', phoenix_sample_apps_dir + '/word_count/dfisan_wordcount_pthreads ' + word_count_input_file)
  elif args.command:
    if args.num is None or args.command is None:
      parser.print_help()
      exit(1)

    exec_time_command(args.num, args.output, args.command)

  if args.result:
    print_all(file_list, 3)
