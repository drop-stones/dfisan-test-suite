// Tests that dfisan can detect overread of local variable.

#include <stdio.h>
#include "util.h"

int main(int argc, char **argv) {
  int x = 100;
  int arr[8] = { 0 };
  
  printf("x = %d\n", x);
  overread(arr, &x);

  return 0;
}
