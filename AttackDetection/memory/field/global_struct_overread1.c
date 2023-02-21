#include "util.h"

struct User u = { "Alice", 100 };

int main(void) {
  u.id;                     // OK
  overread(u.name, &u.id);  // Error: read 'a.id'

  return 0;
}
