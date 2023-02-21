#include "util.h"

void Read(char *str, char *dst) {
  overread(str, dst);
}

int main(void) {
  struct User u = { "Alice", 200 };
  int x = 100;

  Read(u.name, &x);

  return 0;
}
