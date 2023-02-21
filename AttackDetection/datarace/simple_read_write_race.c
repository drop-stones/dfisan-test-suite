#include "test.h"

int Global __attribute__((annotate("dfi_protection")));

void *Thread1(void *x) {
  Global;
  barrier_wait(&barrier);
  return NULL;
}

void *Thread2(void *x) {
  barrier_wait(&barrier);
  Global = 43;
  return NULL;
}

int main() {
  barrier_init(&barrier, 2);
  pthread_t t[2];
  pthread_create(&t[0], NULL, Thread1, NULL);
  pthread_create(&t[1], NULL, Thread2, NULL);
  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
  return 0;
}
