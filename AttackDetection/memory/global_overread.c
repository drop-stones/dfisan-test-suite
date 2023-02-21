#include <stdio.h>

// int x __attribute__((annotate("dfi_protection"))) = 100;
// int arr[8] __attribute__((annotate("dfi_protection")));
int x = 100;
int arr[8];

int main() {
  for (int i = 0; i < 8; i++)
    arr[i] = i;
  
  printf("x = %d\n", x);              // OK!
  printf("arr[-2] = %d\n", arr[-2]);  // Error: read 'x'
  printf("arr[9] = %d\n", arr[9]);  // Error: read 'x'

  return 0;
}
