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

unsigned sen_len;
unsigned ins_len;
unsigned sen_max;
unsigned sen_min;
unsigned ins_max;
unsigned ins_min;

__attribute__((annotate("sensitive"))) struct sensitive dummy;  // for datashield
void *safe_malloc(size_t size) { return malloc(size); }

void print_usage(const char *exe_name) {
  printf("usage: %s <sensitive percentage>\n", exe_name);
}

void *sen_find_max(void *arg) {
  struct sensitive *arr = (struct sensitive *)arg;
  sen_max = 0;
  for (unsigned i = 0; i < sen_len; i++)
    if (sen_max < arr[i].id)
      sen_max = arr[i].id;
  return NULL;
}

void *sen_find_min(void *arg) {
  struct sensitive *arr = (struct sensitive *)arg;
  sen_min = RAND_MAX;
  for (unsigned i = 0; i < sen_len; i++)
    if (sen_min > arr[i].id)
      sen_min = arr[i].id;
  return NULL;
}

void *ins_find_max(void *arg) {
  struct insensitive *arr = (struct insensitive *)arg;
  ins_max = 0;
  for (unsigned i = 0; i < ins_len; i++)
    if (ins_max < arr[i].id)
      ins_max = arr[i].id;
  return NULL;
}

void *ins_find_min(void *arg) {
  struct insensitive *arr = (struct insensitive *)arg;
  ins_min = RAND_MAX;
  for (unsigned i = 0; i < ins_len; i++)
    if (ins_min > arr[i].id)
      ins_min = arr[i].id;
  return NULL;
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
  sen_len = ARR_LEN * ((double)percentage / 100);
  ins_len = ARR_LEN - sen_len;
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

  pthread_t tid[4];

  // Find min and max
  printf("Find min and max...\n");
  pthread_create(&tid[0], NULL, sen_find_max, (void *)sen_arr);
  pthread_create(&tid[1], NULL, sen_find_min, (void *)sen_arr);
  pthread_create(&tid[2], NULL, ins_find_max, (void *)ins_arr);
  pthread_create(&tid[3], NULL, ins_find_min, (void *)ins_arr);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  pthread_join(tid[3], NULL);
  printf("sensitive  : Min = %d, Max = %d\n", sen_min, sen_max);
  printf("insensitive: Min = %d, Max = %d\n", ins_min, ins_max);

  free(sen_arr);
  free(ins_arr);

  return 0;
}
