#include <stdlib.h>
#include "util.h"

int main(void) {
  int *u = (struct User *)malloc(sizeof(struct User));

  free(u);
  free(u);

  return 0;
}
