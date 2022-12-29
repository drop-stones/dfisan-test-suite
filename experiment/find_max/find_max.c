/*  Compilation
 *  clang (-DSAFE_ALLOC) (-DDEBUG) insertion_sort.c
 */

#include "sensitive_struct.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#if SAFE_ALLOC
#include "../safe_alloc.h"
#endif
// #if MOVEC
// int _IO_getc(FILE *stream) { return getc(stream); }
// int _IO_putc(int c, FILE *stream) { return putc(c, stream); }
// #endif

#define ARR_LEN 0x6000000

__attribute__((annotate("sensitive"))) struct sensitive dummy;  // for datashield
void *safe_malloc(size_t size) { return malloc(size); }

void print_usage(const char *exe_name) {
  printf("usage: %s <sensitive percentage>\n", exe_name);
}

unsigned sen_find_max(struct sensitive *arr, unsigned len) {
  unsigned max = 0;
  for (unsigned i = 0; i < len; i++) {
    if (max < arr[i].id)
      max = arr[i].id;
  }
  return max;
}

unsigned ins_find_max(struct insensitive *arr, unsigned len) {
  unsigned max = 0;
  for (unsigned i = 0; i < len; i++) {
    if (max < arr[i].id)
      max = arr[i].id;
  }
  return max;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    print_usage(argv[0]);
    return 0;
  }
  int percentage = atoi(argv[1]);
  if (percentage < 0 || 100 < percentage) {
    print_usage(argv[0]);
    return 0;
  }
  unsigned sen_len = ARR_LEN * ((double)percentage / 100);
  unsigned ins_len = ARR_LEN - sen_len;
  struct sensitive *sen_arr;
#if SAFE_ALLOC
  sen_arr = (struct sensitive *)safe_malloc(sizeof(struct sensitive) * sen_len);  // protection target
#else
  sen_arr = (struct sensitive *)malloc(sizeof(struct sensitive) * sen_len);
#endif
  struct insensitive *ins_arr = (struct insensitive *)malloc(sizeof(struct insensitive) * ins_len);
  printf("sensitive array length = %d\ninsensitive array length = %d\n", sen_len, ins_len);

  // Initialize arrays with random number
  srand(time(NULL));
  printf("Initialize arrays...\n");
  for (unsigned i = 0; i < sen_len; i++)
    sen_arr[i].id = rand();
  for (unsigned i = 0; i < ins_len; i++)
    ins_arr[i].id = rand();

  // Insertion sort
  printf("Find max...\n");
  unsigned sen_max = sen_find_max(sen_arr, sen_len);
  unsigned ins_max = ins_find_max(ins_arr, ins_len);
  printf("sensitive max = %d\ninsensitive max = %d\n", sen_max, ins_max);

  free(sen_arr);
  free(ins_arr);

  return 0;
}
