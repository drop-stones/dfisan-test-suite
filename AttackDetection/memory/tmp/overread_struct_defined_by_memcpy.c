#include <string.h>
#include "util.h"

int main(void) {
  struct User u = { "Alice", 100 };  // Defined by llvm.memcpy
  
  u.id;       // OK!
  u.name[9];   // Miss error because Arr.id and Arr.arr has the same ID
  return 0;
}
