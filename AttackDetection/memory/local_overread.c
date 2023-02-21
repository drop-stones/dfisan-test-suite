// Tests that dfisan can detect overread of local variable.

#include <stdio.h>

int main(int argc, char **argv) {
  // int x __attribute__((annotate("dfi_protection"))) = 100;
  // int arr[8] __attribute__((annotate("dfi_protection")));
  int x = 100;
  int arr[8];

  for (int i = 0; i < 8; i++)
    arr[i] = i;
  
  printf("x = %d\n", x);              // OK!
  printf("arr[12] = %d\n", arr[12]);  // Error: read 'x'

  return 0;
}
