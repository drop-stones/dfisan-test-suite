// Tests that dfisan can detect buffer overflow of local variable.

#include <stdio.h>
#include "util.h"

int main(int argc, char **argv) {
  static int arr[8];
  static int x;

  printf("arr = 0x%zx\n", (size_t)arr);
  printf("&x = 0x%zx\n", (size_t)&x);

  // int idx = ((int)&x - (int)arr) / 4;
  // printf("idx = %d\narr[%d] = %p\n", idx, idx, &arr[idx]);
  // arr[idx] = 200;    // Static buffer overflow
  // arr[9] = 200;      // for asan
  overflow(arr, (char *)&x);

  printf("x = %d (== 100)\n", x); // Error: read broken 'x'

  return 0;
}
