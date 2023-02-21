#include <stdlib.h>
#include <assert.h>
#include "util.h"

int main(void) {
  int *freed = (int *)malloc(sizeof(int));
  *freed = 100;
  printf("*freed = %d\n", *freed);
  free(freed);

  while (1) {
    int *secret = (int *)malloc(sizeof(int));
    *secret = 200;
    if (freed == secret) {
      assert(*freed == *secret);
      printf("*freed = secret = %d\n", *freed);  // Use after reallocation
    }
    free(secret);

    if (freed == secret)
      break;
  }

  return 0;
}