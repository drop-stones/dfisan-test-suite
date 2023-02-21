#include "util.h"

struct User u = { "Alice", 100 };

int main(void) {
  overflow(u.name, (char *)&u.id);
  u.id;      // Error: read broken 'a->id'

  return 0;
}
