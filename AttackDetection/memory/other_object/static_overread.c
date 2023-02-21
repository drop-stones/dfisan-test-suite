// Tests that dfisan can detect overread of local variable.

#include <stdio.h>
#include "util.h"

int main(int argc, char **argv) {
  static int x = 100;
  static int arr[8] = { 0 };

  printf("x = %d\n", x);              // OK!
  overread(arr, &x);

  return 0;
}
