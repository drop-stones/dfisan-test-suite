#if SAFE_ALLOC
#include "../../safe_alloc.h"
#else
#include <stdlib.h>
#define safe_malloc malloc
#endif

void set200(int *ptr) {
  *ptr = 200;
}

int main(void) {
  int *arr = (int *)safe_malloc(sizeof(int) * 10);

  arr[0] = 100;

  set200(&arr[0]);

  arr[0];

  free(arr);

  return 0;
}
