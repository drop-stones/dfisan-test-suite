// Tests that dfisan can detect overflow in local struct.

struct Array {
  char arr[8];
  int id;
};

int main(int argc, char **argv) {
  // static struct Array Arr __attribute__((annotate("dfi_protection")));
  static struct Array Arr;
  Arr.id = 100;
  for (int i = 0; i < 9; i++)
    Arr.arr[i] = 'a';

  Arr.id;   // Error: read broken 'Arr.id'
  return 0;
}