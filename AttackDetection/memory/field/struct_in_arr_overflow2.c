#include <string.h>
#include "util.h"

int main(void) {
  struct User users[8];
  for (int i = 0; i < 8; i++) {
    users[i].id = i;
    memcpy(users[i].name, "aaaaaaaaaa", 10);   // Overflow
  }

  users[0].id;

  return 0;
}
