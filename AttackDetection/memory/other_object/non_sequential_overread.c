#include <stdio.h>
#include "util.h"

int x = 100;
int arr[8];

int main(void) {
  printf("arr = 0x%zx\n", (size_t)arr);
  printf("&x = 0x%zx\n", (size_t)&x);

  // int idx = ((int)&x - (int)arr) / 4;
  // printf("idx = %d\narr[%d] = %p\n", idx, idx, &arr[idx]);
  // arr[idx];   // Global buffer overread
  non_sequential_overread(arr, &x);

  return 0;
}
