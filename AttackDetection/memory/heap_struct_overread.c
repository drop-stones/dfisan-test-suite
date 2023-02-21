// Tests that dfisan can detect overread in heap struct object.

// #if SAFE_ALLOC
// #include "../safe_alloc.h"
// #else
// #define safe_malloc malloc
// #endif

#include <stdlib.h>

#define SIZE 8

struct Array {
  char arr[SIZE];
  int id;
};

int main(int argc, char **argv) {
  // struct Array *a = (struct Array *)safe_malloc(sizeof(struct Array));
  struct Array *a = (struct Array *)malloc(sizeof(struct Array));
  a->id = 100;
  for (int i = 0; i < SIZE + 1; i++)
    a->arr[i] = 'a';
  
  a->id;      // OK!
  a->arr[9];  // Error: read 'a->id'
  free(a);
  return 0;
}
