#define SIZE 8

struct Array {
  char arr[SIZE];
  int id;
};
// struct Array a __attribute__((annotate("dfi_protection")));
struct Array a;

int main(int argc, char **argv) {
  a.id = 100;
  for (int i = 0; i < SIZE; i++)
    a.arr[i] = 'a';

  a.id;             // OK
  a.arr[SIZE + 1];  // Error: read 'a.id'
  return 0;
}
