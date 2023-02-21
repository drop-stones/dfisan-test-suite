#include <stdio.h>
#include "util.h"

int arr[8];
int x = 100;

int main(void) {
  printf("arr = 0x%zx\n", (size_t)arr);
  printf("&x = 0x%zx\n", (size_t)&x);

  arr[9] = 100;       // for asan
  overflow(arr, &x);

  printf("x = %d (== 100)\n", x); // Error: read broken 'x'

  return 0;
}
