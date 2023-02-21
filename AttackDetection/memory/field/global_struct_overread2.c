#include <string.h>
#include "util.h"

struct User u;

int main(void) {
  memcpy(u.name, "Alice", 6);
  u.id = 100;

  u.id;                     // OK
  overread(u.name, &u.id);  // Error: read 'u.id'

  return 0;
}
