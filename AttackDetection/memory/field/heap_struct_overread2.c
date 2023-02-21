// Tests that dfisan can detect overread in heap struct object.
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(void) {
  struct User *u = (struct User *)malloc(sizeof(struct User));
  memcpy(u->name, "Alice", 6);
  u->id = 100;

  overread(u->name, &u->id);
  free(u);

  return 0;
}
