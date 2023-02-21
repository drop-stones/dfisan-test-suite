#include <stdlib.h>

int *ret_ptr(int *p) {
  int x = 100;
  return &x;
}

void deref_ptr(int *p) {
  int y = 200;
  *p;   // Access to y
}

int main(void) {
  int *returned = ret_ptr(NULL);
  deref_ptr(returned);

  return 0;
}
