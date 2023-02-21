// Tests that dfisan can detect overread in local struct.

#include <string.h>
#include "util.h"

int main(void) {
  struct User u = { "Alice", 100 };

  overread(u.name, &u.id);

  return 0;
}
