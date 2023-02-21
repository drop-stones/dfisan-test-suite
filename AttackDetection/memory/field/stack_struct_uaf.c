#include "util.h"

struct User *ret_ptr(void) {
  struct User u = { "Alice", 100 };
  return &u;
}

int main(void) {
  struct User *u = ret_ptr();
  u->id;
  return 0;
}
