#if SAFE_ALLOC
#include "../../safe_alloc.h"
#else
#include <stdlib.h>
#define safe_malloc malloc
#endif

struct Array {
  char arr[8];
  int id;
};

void *malloc_wrapper(size_t size) {
#if SAFE_ALLOC
  // dfisan cannot compile this code...
  // return safe_malloc(size);
  exit(1);
#endif

  return malloc(size);
}

int main(void) {
  struct Array *arr = (struct Array *)malloc_wrapper(sizeof(struct Array));
  arr->id = 100;
  arr->id;

  free(arr);

  return 0;
}
