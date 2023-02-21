// #if SAFE_ALLOC
// #include "../safe_alloc.h"
// #else
// #include <stdlib.h>
// #define safe_malloc malloc
// #endif

#include <stdlib.h>
#include <assert.h>

int main(void) {
  // int *freed = (int *)safe_malloc(sizeof(int));
  int *freed = (int *)malloc(sizeof(int));
  *freed = 100;
  printf("Before: *freed = %d\n", *freed);
  free(freed);

  printf("After: *freed = %d\n", *freed);
  return 0;
}
