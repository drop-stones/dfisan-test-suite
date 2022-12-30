/*  Compilation
 *  clang (-DSAFE_ALLOC) (-DDEBUG) insertion_sort.c
 */

#include "sensitive_struct.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#if SAFE_ALLOC
#include "../safe_alloc.h"
#endif

#define ARR_LEN 0xfffffff

// pthread_create arg
struct arrays {
  struct sensitive *sen_arr;
  unsigned sen_len;
  struct insensitive *ins_arr;
  unsigned ins_len;
};
// pthread_join result
struct results {
  unsigned sen_res;
  unsigned ins_res;
};

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
unsigned sen_find_min(struct sensitive *arr, unsigned len) {
  unsigned min = RAND_MAX;
  for (unsigned i = 0; i < len; i++) {
    if (min > arr[i].id)
      min = arr[i].id;
  }
  return min;
}

unsigned ins_find_max(struct insensitive *arr, unsigned len) {
  unsigned max = 0;
  for (unsigned i = 0; i < len; i++) {
    if (max < arr[i].id)
      max = arr[i].id;
  }
  return max;
}
unsigned ins_find_min(struct insensitive *arr, unsigned len) {
  unsigned min = RAND_MAX;
  for (unsigned i = 0; i < len; i++) {
    if (min > arr[i].id)
      min = arr[i].id;
  }
  return min;
}

void *find_max(void *arg) {
  struct arrays *arrs = (struct arrays *)arg;
  struct results *res = (struct results *)malloc(sizeof(struct results));
  res->sen_res = sen_find_max(arrs->sen_arr, arrs->sen_len);
  res->ins_res = ins_find_max(arrs->ins_arr, arrs->ins_len);
  return res;
}

void *find_min(void *arg) {
  struct arrays *arrs = (struct arrays *)arg;
  struct results *res = (struct results *)malloc(sizeof(struct results));
  res->sen_res = sen_find_min(arrs->sen_arr, arrs->sen_len);
  res->ins_res = ins_find_min(arrs->ins_arr, arrs->ins_len);
  return res;
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

  // Setup pthreads
  struct arrays arrs __attribute__((annotate("dfi_protection"))) = { sen_arr, sen_len, ins_arr, ins_len };
  struct results *min_res, *max_res;
  pthread_t tid[2];

  // Find min and max
  printf("Find min and max...\n");
  pthread_create(&tid[0], NULL, find_min, &arrs);
  pthread_create(&tid[1], NULL, find_max, &arrs);
  pthread_join(tid[0], (void **)&min_res);
  pthread_join(tid[1], (void **)&max_res);
  printf("Max: sensitive = %d, insensitive = %d\n", max_res->sen_res, max_res->ins_res);
  printf("Min: sensitive = %d, insensitive = %d\n", min_res->sen_res, min_res->ins_res);

  free(sen_arr);
  free(ins_arr);
  free(min_res);
  free(max_res);

  return 0;
}
