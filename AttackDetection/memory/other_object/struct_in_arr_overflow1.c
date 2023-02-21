#include <string.h>
#include "util.h"

int main(void) {
  struct User users[8];
  int x = 100;
  for (int i = 0; i < 8; i++) {
    memcpy(users[i].name, "name", 8);
    users[i].id = i;
  }

  overflow(users[0].name, (char *)&x);
  x;

  return 0;
}
