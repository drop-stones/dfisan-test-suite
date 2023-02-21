// Tests that dfisan can detect overread in local struct.

#include <string.h>
#include "util.h"

int main(void) {
  struct User u;
  u.id = 100;
  memcpy(u.name, "Alice", 6);

  overread(u.name, &u.id);

  return 0;
}
