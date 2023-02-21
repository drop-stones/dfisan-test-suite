#include <string.h>
#include "util.h"

void Read(char *str, char *dst) {
  overread(str, dst);
}

int main(void) {
  struct User u;
  memcpy(u.name, "Alice", 6);
  u.id = 100;

  Read(u.name, &u.id);

  return 0;
}
