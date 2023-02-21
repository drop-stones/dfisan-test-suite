#include <stdlib.h>
#include <assert.h>
#include "util.h"

int main(void) {
  int *freed = (int *)malloc(sizeof(int));
  *freed = 100;
  printf("Before: *freed = %d\n", *freed);
  free(freed);

  printf("After: *freed = %d\n", *freed);
  return 0;
}
