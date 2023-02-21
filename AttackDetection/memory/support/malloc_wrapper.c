#include <stdlib.h>

struct Array {
  char arr[8];
  int id;
};

void *malloc_wrapper(size_t size) {
#if DFISAN
  // dfisan cannot compile this code...
  // return safe_malloc(size);
  exit(1);
  return NULL;
#else
  return malloc(size);
#endif
}

int main(void) {
  struct Array *arr = (struct Array *)malloc_wrapper(sizeof(struct Array));
  arr->id = 100;
  arr->id;

  free(arr);

  return 0;
}
