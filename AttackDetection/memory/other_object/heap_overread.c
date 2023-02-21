// Tests that dfisan can detect overread of heap object.

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(int argc, char **argv) {
  int *arr = (int *)malloc(sizeof(int) * 10);
  int *p = (int *)malloc(sizeof(int));

  memset(arr, 0, sizeof(int) * 10);
  *p = 100;

  printf("p = %p, *p = %d\n", (void *)p, *p);
  overread(arr, p);

  free(arr);
  free(p);

  return 0;
}
