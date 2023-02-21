#include <string.h>
#include "util.h"

int main(void) {
  struct User u;
  memcpy(u.name, "Alice", 6);
  u.id = 100;

  overread(u.name, &u.id);

  return 0;
}
