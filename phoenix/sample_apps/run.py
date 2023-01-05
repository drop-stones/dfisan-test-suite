import argparse
import os
from print_stat import print_all

def exec_command(num: int, output: str, command: str):
  for i in range(args.num):
    command = "time -p -v -o " + output + " -a " + command
    print(command)
    os.system(command)

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description = 'run sample apps')
  parser.add_argument('-n', dest='num', type=int)
  parser.add_argument('-o', dest='output', type=str)
  parser.add_argument('--command', type=str)
  parser.add_argument('--all', action='store_const', const=True, default=False)
  args = parser.parse_args()
  # print(args.command)
  # print(args.output)
  # print(args.num)

  if args.all:
    # kmeans
    exec_command(args.num, "kmeans.txt", "kmeans/kmeans-pthread -d 10 -c 10000 -p 10000 -s 10000")
    exec_command(args.num, "tsan_kmeans.txt", "kmeans/tsan_kmeans_pthread -d 10 -c 10000 -p 10000 -s 10000")
    exec_command(args.num, "dfisan_kmeans.txt", "kmeans/dfisan_kmeans_pthread -d 10 -c 1000 -p 10000 -s 10000")

    # pca
    exec_command(args.num, "pca.txt", "pca/pca-pthread -r 1000 -c 1000 -s 1000")
    exec_command(args.num, "tsan_pca.txt", "pca/tsan_pca_pthread -r 1000 -c 1000 -s 1000")
    exec_command(args.num, "dfisan_pca.txt", "pca/dfisan_pca_pthread -r 1000 -c 1000 -s 1000")

    # string_match
    exec_command(args.num, "string_match.txt", "string_match/string_match_pthreads string_match/string_match_datafiles/key_file_500MB.txt")
    exec_command(args.num, "tsan_string_match.txt", "string_match/tsan_string_match_pthreads string_match/string_match_datafiles/key_file_500MB.txt")
    exec_command(args.num, "dfisan_string_match.txt", "string_match/dfisan_string_match_pthreads string_match/string_match_datafiles/key_file_500MB.txt")

    # word_count
    exec_command(args.num, "word_count.txt", "word_count/wordcount_pthreads word_count/word_count_datafiles/word_100MB.txt")
    exec_command(args.num, "tsan_word_count.txt", "word_count/tsan_wordcount_pthreads word_count/word_count_datafiles/word_100MB.txt")
    exec_command(args.num, "dfisan_word_count.txt", "word_count/dfisan_wordcount_pthreads word_count/word_count_datafiles/word_100MB.txt")

    ## print_stat
    print_all()
  else:
    exec_command(args.num, args.output, args.command)
