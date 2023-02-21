// dfisan cannot detect the error because of element insensitivity

#include <string.h>
#include "util.h"

int main(void) {
  struct User users[8];
  for (int i = 0; i < 6; i++) {
    users[i].id = i;
    users[i].name[sizeof(struct User)] = 'a';
    // memcpy(users[i].str, "name", 8);
  }

  users[1].name[0];

  return 0;
}
