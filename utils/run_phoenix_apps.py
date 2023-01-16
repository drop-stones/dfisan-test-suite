import argparse
import os
from time_stat import exec_time_command
from print_stat import print_all


phoenix_sample_apps_dir = os.path.join(os.path.dirname(__file__), '../phoenix/sample_apps')
phoenix_sample_apps_dir = os.path.normpath(phoenix_sample_apps_dir)

file_list = [
  'histogram.txt',
  'tsan_histogram.txt',
  'dfisan_histogram.txt',

  'kmeans.txt',
  'tsan_kmeans.txt',
  'dfisan_kmeans.txt',

  'linear_regression.txt',
  'tsan_linear_regression.txt',
  'dfisan_linear_regression.txt',

  'pca.txt',
  'tsan_pca.txt',
  'dfisan_pca.txt',

  # 'reverse_index.txt',
  # 'tsan_reverse_index.txt',
  # 'dfisan_reverse_index.txt',

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
  parser.add_argument('--name', type=str)
  parser.add_argument('--all', action='store_const', const=True, default=False)
  parser.add_argument('--result', action='store_const', const=True, default=False)
  args = parser.parse_args()

  if args.all or args.name:
    if args.num is None:
      parser.print_help()
      exit(1)

  if args.all or args.name == 'histogram':
    # histogram
    histogram_dir = phoenix_sample_apps_dir + '/histogram/'
    histogram_input_file = histogram_dir + 'histogram_datafiles/large.bmp'
    exec_time_command(args.num, 'histogram.txt',        histogram_dir + 'hist-pthread '        + histogram_input_file)
    exec_time_command(args.num, 'tsan_histogram.txt',   histogram_dir + 'tsan_hist_pthread '   + histogram_input_file)
    exec_time_command(args.num, 'dfisan_histogram.txt', histogram_dir + 'dfisan_hist_pthread ' + histogram_input_file)

  if args.all or args.name == 'kmeans':
    # kmeans
    kmeans_dir = phoenix_sample_apps_dir + '/kmeans/'
    exec_time_command(args.num, 'kmeans.txt',        kmeans_dir + 'kmeans-pthread -d 10 -c 10000 -p 10000 -s 10000')
    exec_time_command(args.num, 'tsan_kmeans.txt',   kmeans_dir + 'tsan_kmeans_pthread -d 10 -c 10000 -p 10000 -s 10000')
    exec_time_command(args.num, 'dfisan_kmeans.txt', kmeans_dir + 'dfisan_kmeans_pthread -d 10 -c 10000 -p 10000 -s 10000')

  if args.all or args.name == 'linear_regression':
    # linear_regression
    linear_regression_dir = phoenix_sample_apps_dir + '/linear_regression/'
    linear_regression_input_file = linear_regression_dir + 'linear_regression_datafiles/key_file_500MB.txt'
    exec_time_command(args.num, 'linear_regression.txt',        linear_regression_dir + 'lreg-pthread '        + linear_regression_input_file)
    exec_time_command(args.num, 'tsan_linear_regression.txt',   linear_regression_dir + 'tsan_lreg_pthread '   + linear_regression_input_file)
    exec_time_command(args.num, 'dfisan_linear_regression.txt', linear_regression_dir + 'dfisan_lreg_pthread ' + linear_regression_input_file)

  if args.all or args.name == 'pca':
    # pca
    pca_dir = phoenix_sample_apps_dir + '/pca/'
    exec_time_command(args.num, 'pca.txt',        pca_dir + 'pca-pthread -r 1000 -c 1000 -s 1000')
    exec_time_command(args.num, 'tsan_pca.txt',   pca_dir + 'tsan_pca_pthread -r 1000 -c 1000 -s 1000')
    exec_time_command(args.num, 'dfisan_pca.txt', pca_dir + 'dfisan_pca_pthread -r 1000 -c 1000 -s 1000')

    # reverse_index
    # reverse_index_dir = phoenix_sample_apps_dir + '/reverse_index/'
    # reverse_index_input_file = reverse_index_dir + 'reverse_index_datafiles/'
    # exec_time_command(args.num, 'reverse_index.txt',        reverse_index_dir + 'reverseindex-pthread ' +        reverse_index_input_file)
    # exec_time_command(args.num, 'tsan_reverse_index.txt',   reverse_index_dir + 'tsan_reverseindex_pthread ' +   reverse_index_input_file)
    # exec_time_command(args.num, 'dfisan_reverse_index.txt', reverse_index_dir + 'dfisan_reverseindex_pthread ' + reverse_index_input_file)

  if args.all or args.name == 'string_match':
    # string_match
    string_match_dir = phoenix_sample_apps_dir + '/string_match/'
    string_match_input_file = string_match_dir + 'string_match_datafiles/key_file_500MB.txt'
    exec_time_command(args.num, 'string_match.txt',        string_match_dir + 'string_match_pthreads '        + string_match_input_file)
    exec_time_command(args.num, 'tsan_string_match.txt',   string_match_dir + 'tsan_string_match_pthreads '   + string_match_input_file)
    exec_time_command(args.num, 'dfisan_string_match.txt', string_match_dir + 'dfisan_string_match_pthreads ' + string_match_input_file)

  if args.all or args.name == 'word_count':
    # word_count
    word_count_dir = phoenix_sample_apps_dir + '/word_count/'
    word_count_input_file = word_count_dir + 'word_count_datafiles/word_100MB.txt'
    exec_time_command(args.num, 'word_count.txt',        word_count_dir + 'wordcount_pthreads '        + word_count_input_file)
    exec_time_command(args.num, 'tsan_word_count.txt',   word_count_dir + 'tsan_wordcount_pthreads '   + word_count_input_file)
    exec_time_command(args.num, 'dfisan_word_count.txt', word_count_dir + 'dfisan_wordcount_pthreads ' + word_count_input_file)

  elif args.command:
    if args.num is None or args.command is None:
      parser.print_help()
      exit(1)
    exec_time_command(args.num, args.output, args.command)

  if args.result:
    print_all(file_list, 3)
