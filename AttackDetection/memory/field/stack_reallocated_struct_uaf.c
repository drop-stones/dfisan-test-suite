#include <stdlib.h>
#include "util.h"

struct User *ret_ptr(struct User *p) {
  struct User u = { "Alice", 100 };
  u.id;
  return &u;
}

void deref_ptr(struct User *u) {
  struct User u2 = { "Bob", 200 };
  u2.id;
  u->id;
}

int main(void) {
  struct User *u = ret_ptr(NULL);
  deref_ptr(u);

  return 0;
}
