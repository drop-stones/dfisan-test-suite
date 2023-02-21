// Tests that dfisan can detect buffer overflow in heap.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(int argc, char **argv) {
  int *arr = (int *)malloc(sizeof(int) * 10);
  int *p = (int *)malloc(sizeof(int));

  memset(arr, 0, sizeof(int) * 10);
  *p = 100;

  printf("arr = %p, arr[0] = %d\n", (void *)arr, arr[0]);
  printf("p = %p, *p = %d\n", (void *)p, *p);

  // arr[12] = 200;  // overwrite '*p'
  // overflow((char *)arr, (char *)p);
  overflow(arr, p);

  printf("arr = %p, arr[0] = %d\n", (void *)arr, arr[0]);
  printf("p = %p, *p = %d\n", (void *)p, *p);   // Error: read broken '*p'

  free(arr);
  free(p);

  return 0;
}
