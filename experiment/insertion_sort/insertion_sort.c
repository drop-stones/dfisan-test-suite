/*  Compilation
 *  clang (-DSAFE_ALLOC) (-DDEBUG) insertion_sort.c
 */

#include "sensitive_struct.h"
#include "../safe_alloc.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define ARR_LEN 0xffff

__attribute__((annotate("sensitive"))) struct sensitive dummy;  // for datashield
void *safe_malloc(size_t size) { return malloc(size); }

void print_usage(const char *exe_name) {
  printf("usage: %s <sensitive percentage>\n", exe_name);
}

unsigned sen_min_after(struct sensitive *arr, unsigned len, unsigned start) {
  unsigned winner = start;
  for (unsigned i = start; i < len; i++)
    if (arr[i].id < arr[winner].id)
      winner = i;
  return winner;
}

void sen_insertion_sort(struct sensitive *arr, unsigned len) {
  for (unsigned i = 0; i < len; i++) {
    unsigned swap = sen_min_after(arr, len, i);
    struct sensitive tmp = arr[i];
    arr[i] = arr[swap];
    arr[swap] = tmp;
  }
}

unsigned ins_min_after(struct insensitive *arr, unsigned len, unsigned start) {
  unsigned winner = start;
  for (unsigned i = start; i < len; i++)
    if (arr[i].id < arr[winner].id)
      winner = i;
  return winner;
}

void ins_insertion_sort(struct insensitive *arr, unsigned len) {
  for (unsigned i = 0; i < len; i++) {
    unsigned swap = ins_min_after(arr, len, i);
    struct insensitive tmp = arr[i];
    arr[i] = arr[swap];
    arr[swap] = tmp;
  }
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
  printf("Insertion sort...\n");
  sen_insertion_sort(sen_arr, sen_len);
  ins_insertion_sort(ins_arr, ins_len);
  printf("Insertion sort completed\n");

#if DEBUG
  // Check the results
  if (sen_len > 1)
    for (unsigned i = 0; i < sen_len - 1; i++)
      assert(sen_arr[i].id <= sen_arr[i+1].id);
  if (ins_len > 1)
    for (unsigned i = 0; i < ins_len - 1; i++)
      assert(ins_arr[i].id <= ins_arr[i+1].id);
  printf("Arrays are sorted correctly\n");
#endif

  free(sen_arr);
  free(ins_arr);

  return 0;
}
