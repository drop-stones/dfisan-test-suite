// Tests that dfisan can detect overread in heap struct object.
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(void) {
  struct User *u = (struct User *)malloc(sizeof(struct User));
  memset(u, 0, sizeof(struct User));

  overread(u->name, &u->id);
  free(u);

  return 0;
}
