#include <string.h>
#include "util.h"

int main(void) {
  struct User users[8];
  for (int i = 0; i < 8; i++) {
    memcpy(users[i].name, "name", 8);
    users[i].id = i;
  }

  users[0].name[9];

  return 0;
}
