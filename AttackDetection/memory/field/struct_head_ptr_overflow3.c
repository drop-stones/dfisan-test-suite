#include "util.h"

int main(void) {
  struct User u = { "Alice", 100 };
  overflow(u.name, (char *)&u.id);

  u.id;   // Error

  return 0;
}
