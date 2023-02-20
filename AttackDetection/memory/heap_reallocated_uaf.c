#if SAFE_ALLOC
#include "../safe_alloc.h"
#else
#include <stdlib.h>
#define safe_malloc malloc
#endif

#include <assert.h>


int main(void) {
  int *freed = (int *)safe_malloc(sizeof(int));
  *freed = 100;
  printf("*freed = %d\n", *freed);
  free(freed);

  while (1) {
    int *secret = (int *)safe_malloc(sizeof(int));
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