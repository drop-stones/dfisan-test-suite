#include "test.h"

int Global __attribute__((annotate("dfi_protection")));

void *Thread(void *x) {
  Global = 100;
  barrier_wait(&barrier);
  Global;
}

int main() {
  barrier_init(&barrier, 2);
  pthread_t t[2];
  pthread_create(&t[0], NULL, Thread, NULL);
  pthread_create(&t[1], NULL, Thread, NULL);
  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
  return 0;
}
