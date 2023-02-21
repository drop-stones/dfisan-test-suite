// #if SAFE_ALLOC
// #include "../../safe_alloc.h"
// #else
// #include <stdlib.h>
// #define safe_malloc malloc
// #endif

#include <stdlib.h>

struct Ptr {
  int *ptr;
};

void set200(int *ptr) {
  *ptr = 200;
}

int main(void) {
  // struct Ptr *p = (struct Ptr *)safe_malloc(sizeof(struct Ptr));
  // p->ptr = (int *)safe_malloc(sizeof(int) * 10);
  struct Ptr *p = (struct Ptr *)malloc(sizeof(struct Ptr));
  p->ptr = (int *)malloc(sizeof(int) * 10);

  p->ptr[0] = 100;

  set200(&p->ptr[0]);

  p->ptr[0];

  free(p->ptr);
  free(p);

  return 0;
}
