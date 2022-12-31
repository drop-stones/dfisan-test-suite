#include <stdio.h>

int x __attribute__((annotate("dfi_protection"))) = 100;  // 0x__3f0
int arr[8] __attribute__((annotate("dfi_protection")));   // 0x__3c0

int main(void) {
  printf("arr = 0x%zx\n", (size_t)arr);
  printf("&x = 0x%zx\n", (size_t)&x);

  int idx = ((int)&x - (int)arr) / 4;
  printf("idx = %d\narr[%d] = %p\n", idx, idx, &arr[idx]);
  arr[idx] = 200;    // Local buffer overflow
  arr[9] = 200;      // for asan

  printf("x = %d (== 100)\n", x); // Error: read broken 'x'

  return 0;
}
