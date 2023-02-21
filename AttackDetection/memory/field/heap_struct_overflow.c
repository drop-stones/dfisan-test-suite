// Tests that dfisan can detect buffer overflow in heap struct object.
#include <stdlib.h>
#include "util.h"

int main(void) {
  struct User *u = (struct User *)malloc(sizeof(struct User));
  u->id = 100;
  overflow(u->name, (char *)&u->id);

  u->id;      // Error: read broken 'u->id'
  free(u);

  return 0;
}
