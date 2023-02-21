#include <string.h>

struct Array {
  char arr[8];
  int id;
};

int main(int argc, char **argv) {
  struct Array Arr = { "hello", 100 };  // Defined by llvm.memcpy
  
  Arr.id;       // OK!
  Arr.arr[9];   // Miss error because Arr.id and Arr.arr has the same ID
  return 0;
}
