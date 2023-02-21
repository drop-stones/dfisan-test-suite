#include "util.h"

struct User u;

int main(void) {
  memcpy(u.name, "Alice", 6);
  u.id = 100;

  non_sequential_overflow(u.name, (char *)&u.id);
  u.id;

  return 0;
}