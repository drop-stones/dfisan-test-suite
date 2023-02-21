#include <stdio.h>
#include "util.h"

int arr[8] = { 0 };
int x = 100;

int main() {
  
  printf("x = %d\n", x);  // OK!
  overread(arr, &x);      // Error: read 'x';

  return 0;
}
