#include <stdlib.h>
#include "util.h"

int main(void) {
  struct User *u = (struct User *)malloc(sizeof(struct User));
  u->id = 100;
  printf("Before: u->id = %d\n", u->id);
  free(u);

  printf("After: u->id = %d\n", u->id);
  return 0;
}
