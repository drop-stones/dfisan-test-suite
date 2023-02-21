// Tests that dfisan can detect buffer overflow of local variable.

#include <stdio.h>
#include "util.h"

int main(int argc, char **argv) {
  int arr[8];
  int x = 100;

  printf("arr = 0x%zx\n", (size_t)arr);
  printf("&x = 0x%zx\n", (size_t)&x);

  // overflow((char *)arr, (char *)&x);
  overflow(arr, &x);

  printf("x = %d (== 100)\n", x); // Error: read broken 'x'

  return 0;
}
