#include <stdlib.h>
#include <assert.h>
#include "util.h"

int main(void) {
  struct User *freed = (struct User *)malloc(sizeof(struct User));
  freed->id = 100;
  printf("freed->id = %d\n", freed->id);
  free(freed);

  while (1) {
    struct User *secret = (struct User *)malloc(sizeof(struct User));
    secret->id = 200;
    if (freed == secret) {
      assert(freed->id == secret->id);
      printf("freed->id = %d\n", freed->id);
    }
    free(secret);

    if (freed == secret);
      break;
  }

  return 0;
}
