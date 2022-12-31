// RUN: %clang_dfisan %s -o %t
// RUN: !%run %t
//
// REQUIRES: x86_64-target-arch

// Tests that dfisan can detect buffer overflow of local variable.

#include <stdio.h>

int main(int argc, char **argv) {
  static int arr[8] __attribute__((annotate("dfi_protection")));   // 0x__3c0
  static int x __attribute__((annotate("dfi_protection"))) = 100;  // 0x__3f0

  printf("arr = 0x%zx\n", (size_t)arr);
  printf("&x = 0x%zx\n", (size_t)&x);

  int idx = ((int)&x - (int)arr) / 4;
  printf("idx = %d\narr[%d] = %p\n", idx, idx, &arr[idx]);
  arr[idx] = 200;    // Static buffer overflow

  printf("x = %d (== 100)\n", x); // Error: read broken 'x'

  return 0;
}
