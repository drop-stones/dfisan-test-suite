#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "../safe_alloc.h"

void *Thread1(void *p) {
  *(int*)p = 42;
  return 0;
}

void *Thread2(void *p) {
  *(int*)p = 44;
  return 0;
}

__attribute__((noinline)) void *alloc() {
#if SAFE_ALLOC
  // dfisan cannot compile it
  // return safe_malloc(99);
  exit(0);
  return NULL;
#else
  return malloc(99);
#endif
}

void *AllocThread(void* arg) {
  return alloc();
}

int main() {
  int *p = 0;
  pthread_t t[2];
  pthread_create(&t[0], 0, AllocThread, 0);
  pthread_join(t[0], (void **)&p);
  // print_address("addr=", 1, p);
  // p = (int *)safe_malloc(99);
  pthread_create(&t[0], 0, Thread1, p);
  pthread_create(&t[1], 0, Thread2, p);
  pthread_join(t[0], 0);
  pthread_join(t[1], 0);
  return 0;
}
