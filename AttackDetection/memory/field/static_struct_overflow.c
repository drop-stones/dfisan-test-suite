// Tests that dfisan can detect overflow in local struct.

#include "util.h"

int main(void) {
  static struct User u;
  u.id = 100;
  overflow(u.name, (char *)&u.id);

  u.id;   // Error: read broken 'Arr.id'
  return 0;
}
